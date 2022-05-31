<?php 

function lib4ri_pub_db_crunch_abstract($dom, $params){
    $xpath = new DOMXPath($dom);
    $abstractDomNode = $xpath->query('//dc:description/abstract/ce:para')[0];
    $abstractXML = $dom->saveXML($abstractDomNode);
    //$abstractXML = str_replace('inf>', 'sub>', $abstractXML);
    
    $abstract = str_replace('</ce:para>', '', str_replace('<ce:para>', '', $abstractXML));

    $abstract = html_entity_decode($abstract);
//    $abstract = strip_tags($abstract, variable_get('lib4ri_pub_db_abstr_tags'));
    $abstract = str_replace('<inf>', '<sub>', $abstract);
    $abstract = str_replace('</inf>', '</sub>', $abstract);
    $abstract = str_replace('<i>', '<em>', $abstract);
    $abstract = str_replace('</i>', '</em>', $abstract);
    $abstract = htmlspecialchars($abstract);
    $abstract = trim(preg_replace('/\s+/', ' ',$abstract));
    $abstractDomNode->nodeValue = $abstract;
    return $dom;
}

function lib4ri_pub_db_crunch_title($dom, $params){
    $xpath = new DOMXPath($dom);
    $titleDomNode = $xpath->query('//citation-title/titletext')[0];
    $titleXML = $dom->saveXML($titleDomNode);
    
    $title = str_replace('</titletext>', '', str_replace('<titletext>', '', $titleXML));
    $title = html_entity_decode($title);
//    $title = strip_tags($title, variable_get('lib4ri_pub_db_title_tags'));
    $title = str_replace('<inf>', '<sub>', $title);
    $title = str_replace('</inf>', '</sub>', $title);
    $title = str_replace('<i>', '<em>', $title);
    $title = str_replace('</i>', '</em>', $title);
    $title = htmlspecialchars($title);
    $title = trim(preg_replace('/\s+/', ' ',$title));
    $titleDomNode->nodeValue = $title;
    return $dom;
}


function lib4ri_pub_db_decimate_many_authors($dom, $params){
    $xpath = new DOMXPath($dom);
    $authors = $xpath->query(variable_get('lib4ri_pub_db_auth_xpath_query'));
    $auth_n = $authors->length;
    if ($auth_n > $params['threshold']){
        $count = 0;
        $author_list = '';
        foreach ($authors as $author){
            $count += 1;
            
             $name_parts = $author->getElementsByTagName('namePart');
            foreach ($name_parts as $name_part){
                if ($name_part->getAttribute('type')=='family'){
                    $f_name = $name_part->nodeValue;
                }
                if ($name_part->getAttribute('type')=='given'){
                    $g_name = $name_part->nodeValue;
                }
            }
            $author_list .= $f_name.', '.$g_name.'|';
            
            $remove = TRUE;
            $fourri_node = $author->getElementsByTagName('fourri')[0];
            if (!is_null($fourri_node)){
                $fourri = $fourri_node->nodeValue;
                if ($fourri == 'true'){
                    $remove = FALSE;
                }
            }
            if ($count <= $params['first']){
                $remove = FALSE;
            }
            if ($count > $auth_n-$params['last']){
                $remove = FALSE;
            }
            
            if ($remove){
                $author->parentNode->removeChild($author);
            }
        }
        
         $extension = $xpath->query("//mods:mods/mods:extension")[0];
        if (is_null($extension)){
            $extension = $dom->createElement('extension');
            $dom->documentElement->appendChild($extension);
        }
        $orig_auth_list = $dom->createElement('originalAuthorList', rtrim($author_list,'|'));
        $extension->appendchild($orig_auth_list);
    }
    return $dom;
}

function lib4ri_pub_db_cruch_given_name($dom, $params){
//    module_load_include('inc', 'lib4ridora', 'includes/utilities.author');
    $xpath = new DOMXPath($dom);
    $authors = $xpath->query(variable_get('lib4ri_pub_db_auth_xpath_query'));
    
    foreach ($authors as $author){
        $name_parts = $author->getElementsByTagName('namePart');
        foreach ($name_parts as $name_part){
            if ($name_part->getAttribute('type')=='given'){
                $name_part->nodeValue = lib4ri_pub_db_unspace_name_given($name_part->nodeValue);
            }
        }
    }
    return $dom;
}

function lib4ri_pub_db_spot_internal_authors($dom, $params){
//    $xpath = new DOMXPath($dom);
    $authors = $dom->getElementsByTagName("abstracts-retrieval-response")->item(0)->getElementsByTagName("authors")->item(0)->getElementsByTagName("author");
    foreach ($authors as $author){
        $affiliations = $author->getElementsByTagName('affiliation');
        foreach ($affiliations as $affiliation){
            if (in_array($affiliation->getAttribute('id'), explode(',',variable_get('lib4ri_pub_db_scopus_affil_ids')))){
                $author->setAttribute('fourri', 'true');
            }
        }
    }
    return $dom;
}

function lib4ri_pub_db_spot_internal_authors_crossref($dom, $params){
    $xpath = new DOMXPath($dom);
    $authors = $xpath->query('//contributors/person_name[@contributor_role="author"]');
    
    $affil_strs = explode('|',variable_get('lib4ri_pub_db_xref_affiliation_strings'));
    foreach ($authors as $author){
        $affiliations = $author->getElementsByTagName('affiliation');
        foreach ($affiliations as $affiliation){
            foreach ($affil_strs as $affil_str){
                if(strpos($affiliation->nodeValue, $affil_str) !== FALSE){
                    $author->setAttribute('fourri', 'true');
                }
            }
        }
    }
    return $dom;
}


function lib4ri_pub_db_crunch_keywords($dom, $params){
    if(variable_get('lib4ri_pub_db_kw_lc')){
        $keywords = $dom->getElementsByTagName("abstracts-retrieval-response")->item(0)->getElementsByTagName("authkeywords")->item(0)->getElementsByTagName("author-keyword");
        foreach ($keywords as $keyword){
            $keyword->nodeValue = strtolower($keyword->nodeValue);
        }
    }
    return $dom;
}

function lib4ri_pub_db_crunch_confdate($dom, $params){
    $num2month = array('1' => 'January',
                       '2' => 'February',
                       '3' => 'March',
                       '4' => 'April',
                       '5' => 'May',
                       '6' => 'June',
                       '7' => 'July',
                       '8' => 'August',
                       '9' => 'September',
                      '01' => 'January',
                      '02' => 'February',
                      '03' => 'March',
                      '04' => 'April',
                      '05' => 'May',
                      '06' => 'June',
                      '07' => 'July',
                      '08' => 'August',
                      '09' => 'September',
                      '10' => 'October',
                      '11' => 'November',
                      '12' => 'December',
    );
    
    $xpath = new DOMXPath($dom);
    $date_element = $xpath->query(variable_get('lib4ri_pub_db_conf_date_xpath_query'))[0];
//    $date = trim(preg_replace('/\s\s+/', ' ', $date_element->nodeValue));
    $date = str_replace("\n", '', $date_element->nodeValue);
    $dates = explode('-', $date);
    if (sizeof($dates) >= 1){
        $start = explode('.', $dates[0]);
        $start[2] = ltrim($start[2], '0');
    }
    if (sizeof($dates) >= 1){
        $end = explode('.', $dates[1]);
        $end[2] = ltrim($end[2], '0');
    }
    
    if (empty($dates[1]) OR $dates[1]==''){
        if (empty($start[2]) OR $start[2]==''){
//            05.2017 –> May 2017 
            $date_element->nodeValue = "{$num2month[$start[1]]} $start[0]";
        }
        else{
//            01.05.2017 –> May 1, 2017
            $date_element->nodeValue = "{$num2month[$start[1]]} $start[2]. $start[0]";
        }
    }
    elseif ($start[0] != $end[0]){
        //31.12.16-05.1.17 –> December 31, 2016 – January 5, 2017
        $date_element->nodeValue = "{$num2month[$start[1]]} $start[2], $start[0] - {$num2month[$end[1]]} $end[2], $end[0]";
    }
    elseif ($start[1] != $end[1]){
        //30.6-04.7.2017 -> June 30 – July 4, 2017
        $date_element->nodeValue = "{$num2month[$start[1]]} $start[2] - {$num2month[$end[1]]} $end[2], $start[0]";
    }
    else{
        //1.-2.6.2017 -> June 1-2, 2017
        $date_element->nodeValue = "{$num2month[$start[1]]} $start[2]-$end[2], $start[0]";
    }
    
    return $dom;
}

function lib4ri_pub_db_crunch_conf_place($dom, $params){
    $iso3166_a3 = array(
        'ABW'=>'Aruba',
        'AFG'=>'Afghanistan',
        'AGO'=>'Angola',
        'AIA'=>'Anguilla',
        'ALA'=>'Åland Islands',
        'ALB'=>'Albania',
        'AND'=>'Andorra',
        'ARE'=>'United Arab Emirates',
        'ARG'=>'Argentina',
        'ARM'=>'Armenia',
        'ASM'=>'American Samoa',
        'ATA'=>'Antarctica',
        'ATF'=>'French Southern Territories',
        'ATG'=>'Antigua and Barbuda',
        'AUS'=>'Australia',
        'AUT'=>'Austria',
        'AZE'=>'Azerbaijan',
        'BDI'=>'Burundi',
        'BEL'=>'Belgium',
        'BEN'=>'Benin',
        'BES'=>'Bonaire, Sint Eustatius and Saba',
        'BFA'=>'Burkina Faso',
        'BGD'=>'Bangladesh',
        'BGR'=>'Bulgaria',
        'BHR'=>'Bahrain',
        'BHS'=>'Bahamas',
        'BIH'=>'Bosnia and Herzegovina',
        'BLM'=>'Saint Barthélemy',
        'BLR'=>'Belarus',
        'BLZ'=>'Belize',
        'BMU'=>'Bermuda',
        'BOL'=>'Bolivia, Plurinational State of',
        'BRA'=>'Brazil',
        'BRB'=>'Barbados',
        'BRN'=>'Brunei Darussalam',
        'BTN'=>'Bhutan',
        'BVT'=>'Bouvet Island',
        'BWA'=>'Botswana',
        'CAF'=>'Central African Republic',
        'CAN'=>'Canada',
        'CCK'=>'Cocos (Keeling) Islands',
        'CHE'=>'Switzerland',
        'CHL'=>'Chile',
        'CHN'=>'China',
        'CIV'=>'Côte d\'Ivoire',
        'CMR'=>'Cameroon',
        'COD'=>'Congo, the Democratic Republic of the',
        'COG'=>'Congo',
        'COK'=>'Cook Islands',
        'COL'=>'Colombia',
        'COM'=>'Comoros',
        'CPV'=>'Cape Verde',
        'CRI'=>'Costa Rica',
        'CUB'=>'Cuba',
        'CUW'=>'Curaçao',
        'CXR'=>'Christmas Island',
        'CYM'=>'Cayman Islands',
        'CYP'=>'Cyprus',
        'CZE'=>'Czech Republic',
        'DEU'=>'Germany',
        'DJI'=>'Djibouti',
        'DMA'=>'Dominica',
        'DNK'=>'Denmark',
        'DOM'=>'Dominican Republic',
        'DZA'=>'Algeria',
        'ECU'=>'Ecuador',
        'EGY'=>'Egypt',
        'ERI'=>'Eritrea',
        'ESH'=>'Western Sahara',
        'ESP'=>'Spain',
        'EST'=>'Estonia',
        'ETH'=>'Ethiopia',
        'FIN'=>'Finland',
        'FJI'=>'Fiji',
        'FLK'=>'Falkland Islands (Malvinas)',
        'FRA'=>'France',
        'FRO'=>'Faroe Islands',
        'FSM'=>'Micronesia, Federated States of',
        'GAB'=>'Gabon',
        'GBR'=>'United Kingdom',
        'GEO'=>'Georgia',
        'GGY'=>'Guernsey',
        'GHA'=>'Ghana',
        'GIB'=>'Gibraltar',
        'GIN'=>'Guinea',
        'GLP'=>'Guadeloupe',
        'GMB'=>'Gambia',
        'GNB'=>'Guinea-Bissau',
        'GNQ'=>'Equatorial Guinea',
        'GRC'=>'Greece',
        'GRD'=>'Grenada',
        'GRL'=>'Greenland',
        'GTM'=>'Guatemala',
        'GUF'=>'French Guiana',
        'GUM'=>'Guam',
        'GUY'=>'Guyana',
        'HKG'=>'Hong Kong',
        'HMD'=>'Heard Island and McDonald Islands',
        'HND'=>'Honduras',
        'HRV'=>'Croatia',
        'HTI'=>'Haiti',
        'HUN'=>'Hungary',
        'IDN'=>'Indonesia',
        'IMN'=>'Isle of Man',
        'IND'=>'India',
        'IOT'=>'British Indian Ocean Territory',
        'IRL'=>'Ireland',
        'IRN'=>'Iran, Islamic Republic of',
        'IRQ'=>'Iraq',
        'ISL'=>'Iceland',
        'ISR'=>'Israel',
        'ITA'=>'Italy',
        'JAM'=>'Jamaica',
        'JEY'=>'Jersey',
        'JOR'=>'Jordan',
        'JPN'=>'Japan',
        'KAZ'=>'Kazakhstan',
        'KEN'=>'Kenya',
        'KGZ'=>'Kyrgyzstan',
        'KHM'=>'Cambodia',
        'KIR'=>'Kiribati',
        'KNA'=>'Saint Kitts and Nevis',
        'KOR'=>'Korea, Republic of',
        'KWT'=>'Kuwait',
        'LAO'=>'Lao People\'s Democratic Republic',
        'LBN'=>'Lebanon',
        'LBR'=>'Liberia',
        'LBY'=>'Libya',
        'LCA'=>'Saint Lucia',
        'LIE'=>'Liechtenstein',
        'LKA'=>'Sri Lanka',
        'LSO'=>'Lesotho',
        'LTU'=>'Lithuania',
        'LUX'=>'Luxembourg',
        'LVA'=>'Latvia',
        'MAC'=>'Macao',
        'MAF'=>'Saint Martin (French part)',
        'MAR'=>'Morocco',
        'MCO'=>'Monaco',
        'MDA'=>'Moldova, Republic of',
        'MDG'=>'Madagascar',
        'MDV'=>'Maldives',
        'MEX'=>'Mexico',
        'MHL'=>'Marshall Islands',
        'MKD'=>'Macedonia, the former Yugoslav Republic of',
        'MLI'=>'Mali',
        'MLT'=>'Malta',
        'MMR'=>'Myanmar',
        'MNE'=>'Montenegro',
        'MNG'=>'Mongolia',
        'MNP'=>'Northern Mariana Islands',
        'MOZ'=>'Mozambique',
        'MRT'=>'Mauritania',
        'MSR'=>'Montserrat',
        'MTQ'=>'Martinique',
        'MUS'=>'Mauritius',
        'MWI'=>'Malawi',
        'MYS'=>'Malaysia',
        'MYT'=>'Mayotte',
        'NAM'=>'Namibia',
        'NCL'=>'New Caledonia',
        'NER'=>'Niger',
        'NFK'=>'Norfolk Island',
        'NGA'=>'Nigeria',
        'NIC'=>'Nicaragua',
        'NIU'=>'Niue',
        'NLD'=>'Netherlands',
        'NOR'=>'Norway',
        'NPL'=>'Nepal',
        'NRU'=>'Nauru',
        'NZL'=>'New Zealand',
        'OMN'=>'Oman',
        'PAK'=>'Pakistan',
        'PAN'=>'Panama',
        'PCN'=>'Pitcairn',
        'PER'=>'Peru',
        'PHL'=>'Philippines',
        'PLW'=>'Palau',
        'PNG'=>'Papua New Guinea',
        'POL'=>'Poland',
        'PRI'=>'Puerto Rico',
        'PRK'=>'Korea, Democratic People\'s Republic of',
        'PRT'=>'Portugal',
        'PRY'=>'Paraguay',
        'PSE'=>'Palestinian Territory, Occupied',
        'PYF'=>'French Polynesia',
        'QAT'=>'Qatar',
        'REU'=>'Réunion',
        'ROU'=>'Romania',
        'RUS'=>'Russian Federation',
        'RWA'=>'Rwanda',
        'SAU'=>'Saudi Arabia',
        'SDN'=>'Sudan',
        'SEN'=>'Senegal',
        'SGP'=>'Singapore',
        'SGS'=>'South Georgia and the South Sandwich Islands',
        'SHN'=>'Saint Helena, Ascension and Tristan da Cunha',
        'SJM'=>'Svalbard and Jan Mayen',
        'SLB'=>'Solomon Islands',
        'SLE'=>'Sierra Leone',
        'SLV'=>'El Salvador',
        'SMR'=>'San Marino',
        'SOM'=>'Somalia',
        'SPM'=>'Saint Pierre and Miquelon',
        'SRB'=>'Serbia',
        'SSD'=>'South Sudan',
        'STP'=>'Sao Tome and Principe',
        'SUR'=>'Suriname',
        'SVK'=>'Slovakia',
        'SVN'=>'Slovenia',
        'SWE'=>'Sweden',
        'SWZ'=>'Swaziland',
        'SXM'=>'Sint Maarten (Dutch part)',
        'SYC'=>'Seychelles',
        'SYR'=>'Syrian Arab Republic',
        'TCA'=>'Turks and Caicos Islands',
        'TCD'=>'Chad',
        'TGO'=>'Togo',
        'THA'=>'Thailand',
        'TJK'=>'Tajikistan',
        'TKL'=>'Tokelau',
        'TKM'=>'Turkmenistan',
        'TLS'=>'Timor-Leste',
        'TON'=>'Tonga',
        'TTO'=>'Trinidad and Tobago',
        'TUN'=>'Tunisia',
        'TUR'=>'Turkey',
        'TUV'=>'Tuvalu',
        'TWN'=>'Taiwan, Province of China',
        'TZA'=>'Tanzania, United Republic of',
        'UGA'=>'Uganda',
        'UKR'=>'Ukraine',
        'UMI'=>'United States Minor Outlying Islands',
        'URY'=>'Uruguay',
        'USA'=>'United States',
        'UZB'=>'Uzbekistan',
        'VAT'=>'Holy See (Vatican City State)',
        'VCT'=>'Saint Vincent and the Grenadines',
        'VEN'=>'Venezuela, Bolivarian Republic of',
        'VGB'=>'Virgin Islands, British',
        'VIR'=>'Virgin Islands, U.S.',
        'VNM'=>'Viet Nam',
        'VUT'=>'Vanuatu',
        'WLF'=>'Wallis and Futuna',
        'WSM'=>'Samoa',
        'YEM'=>'Yemen',
        'ZAF'=>'South Africa',
        'ZMB'=>'Zambia',
        'ZWE'=>'Zimbabwe'
    );
}
/**
 * Copied from lib4ridora module
 * TODO: FIX: (René M. -> RenéM.)
 */
/*
 * function to remove spaces from initials in 'given name' where needed.
 *
 * Example of initials (types of given name) that can be treated here:
 *	"F. M."          =>  "F.M."
 *	"Jan &#197;. D." =>  "Jan &#197;.D."
 *	"F. &#xD6;."     =>  "F.&#xD6;."
 *	"Chr. E. Th."    =>  "Chr.E.Th."
 *	"H.R. J&#252;rg" =>  "H.R. J&#252;rg"
 */
function lib4ri_pub_db_unspace_name_given( $nameGiven ) {
    if ( !strpos($nameGiven,".") ) { return $nameGiven; }
    $given = preg_replace("/\s+\./",".",trim($nameGiven));	// no space in front of dots, optional/convention
    $given = preg_replace("/\s+/","  ",$given);			// ensure (two) normal space(s), required!
    if ( strcmp($given,$nameGiven) === 0 ) { return $nameGiven; }
    $regExAry = array(	/* looking for terms where we need to keep spaces */
        "/\s[A-Z]([A-Z]+|[a-z]+)\s/",				/* e.g. ' Frank ' or ' DeLuca ' */
        "/\s\&\#[0-9|x|X|A-Fa-f]{1,4};\w*\s/",			/* e.g. ' Özmir ' */
        "/\s[A-Z][a-z]{0,1}&#[0-9|x|X|A-Fa-f]{1,4};\w*\s/",		/* e.g. ' Jürg ' */
    );
    $spacedAry = array();		// only for terms that need spaces around
    foreach( $regExAry as $regEx ) {
        $matchAry = array();
        preg_match_all( $regEx, " {$given} ", $matchAry );
        if ( @empty($matchAry[0]) ) { continue; }
        $spacedAry = array_merge( $spacedAry, $matchAry[0] );
    }
    $given = str_replace(" ","",$given);	// now removing all spaces...
    if ( @empty($spacedAry) ) { return $given; }
    foreach( $spacedAry as $spaced ) {  	// ...and adding 'spaced' terms
        $given = str_replace(trim($spaced," "), $spaced, $given);
    }
    return str_replace("  "," ",trim($given) );
}

function lib4ri_pub_db_res_data_filter_publisher($dom, $params){
    module_load_include('inc', 'lib4ri_pub_db', 'includes/functions');
//    $publishers = explode("\n", trim(variable_get('lib4ri_pub_db_resdata_enrich_publishers')));
    $publishers = lib4ri_pub_db_get_data_publishers(TRUE);
    $xpath = new DOMXPath($dom);
    $items = $xpath->query('//results/item');
    foreach($items as $item){
        $found = false;
        foreach($publishers as $publisher){
            if (strpos(trim($publisher->publisher_string), $item->getElementsByTagName("publisher")->item(0)->nodeValue) !== false){
                $found = true;
                
                $related_identifiers = $xpath->query("descendant::relatedIdentifiers/item", $item);
                $allowed_relation_found = FALSE;
                if (isset($publisher->allowed_rel_types) and $publisher->allowed_rel_types != ''){
                    $relation_types = explode(',', trim($publisher->allowed_rel_types));
                    foreach($related_identifiers as $identifier){
                        if(in_array($identifier->getElementsByTagName("relationType")[0]->nodeValue, $relation_types)){
                            $allowed_relation_found = TRUE;
                            break;
                        }
                    }
                    if($allowed_relation_found == FALSE){
                        $item->parentNode->removeChild($item);
                    }
                }
                
                if (isset($publisher->forbidden_rel_types) and $publisher->forbidden_rel_types != ''){
                    $relation_types = explode(',', trim($publisher->forbidden_rel_types));
                    foreach($related_identifiers as $identifier){
                        if(in_array($identifier->getElementsByTagName("relationType")[0]->nodeValue, $relation_types)){
                            $item->parentNode->removeChild($item);
                        }
                    }
                }
                
                if (isset($publisher->function) and $publisher->function != ''){
                    $fun = $publisher->function;
                    $dom = $fun($dom, $xpath, $item);
                }
                break;
            }
        }
        if($found == false){
            $item->parentNode->removeChild($item);
        }
    }
    
    return $dom;
}

function lib4ri_pub_db_res_data_filter_relation_type($dom, $params){
    $relation_types = explode(',', trim(variable_get('lib4ri_pub_db_resdata_enrich_relations', 'IsSupplementTo')));
    $xpath = new DOMXPath($dom);
    $items = $xpath->query('//results/item/relatedIdentifiers/item');
    foreach($items as $item){
        $found = false;
        foreach($relation_types as $type){
            if (strpos(trim($type), $item->getElementsByTagName("relationType")->item(0)->nodeValue) !== false){
                $found = true;
                break;
            }
        }
        if($found == false){
            $item->parentNode->removeChild($item);
        }
    }
    
    
    return $dom;
}

function hep_discard_appended_version($dom, $xpath, $item){
    $publishers = lib4ri_pub_db_get_data_publishers(TRUE);
    
    
    
    return $dom;
}