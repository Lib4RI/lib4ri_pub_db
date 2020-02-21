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
    $start = explode('.', $dates[0]);
    $end = explode('.', $dates[1]);
    
    if (empty($dates[1]) OR $dates[1]==''){
        if (empty($start[2]) OR $start[2]==''){
//            05.2017 –> May 2017 
        }
        else{
//            01.05.2017 –> May 1, 2017 
        }
    }
    elseif ($start[0] != $end[0]){
        //31.12.16-05.1.17 –> December 31, 2016 – January 5, 2017
    }
    elseif ($start[1] != $end[1]){
        //30.6-04.7.2017 -> June 30 – July 4, 2017 
    }
    else{
        //1.-2.6.2017 -> June 1-2, 2017
        $date_element->nodeValue = "{$num2month[$start[1]]} $start[2]-$end[2], $start[0]";
    }
    
    return $dom;
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