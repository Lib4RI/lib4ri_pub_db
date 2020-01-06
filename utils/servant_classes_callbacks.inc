<?php 

function lib4ri_pub_db_crunch_abstract($dom, $params){
    $xpath = new DOMXPath($dom);
    $abstractDomNode = $xpath->query('//dc:description/abstract/ce:para')[0];
    $abstractXML = $dom->saveXML($abstractDomNode);
    //$abstractXML = str_replace('inf>', 'sub>', $abstractXML);
    
    $abstract = str_replace('</ce:para>', '', str_replace('<ce:para>', '', $abstractXML));
     $abstract = html_entity_decode($abstract);
     $abstract = strip_tags($abstract, variable_get('lib4ri_pub_db_abstr_tags'));
     $abstract = str_replace('<inf>', '<sub>', $abstract);
     $abstract = str_replace('</inf>', '</sub>', $abstract);
     $abstract = str_replace('<i>', '<em>', $abstract);
     $abstract = str_replace('</i>', '</em>', $abstract);
     $abstract = htmlspecialchars($abstract);

    $abstractDomNode->nodeValue = $abstract;
    return $dom;
}

function lib4ri_pub_db_crunch_title($dom, $params){
    $xpath = new DOMXPath($dom);
    $titleDomNode = $xpath->query('//citation-title/titletext')[0];
    $titleXML = $dom->saveXML($titleDomNode);
    
    $title = str_replace('</title>', '', str_replace('<title>', '', $titleXML));
    $title = html_entity_decode($title);
    $title = strip_tags($title, variable_get('lib4ri_pub_db_title_tags'));
    $title = str_replace('<inf>', '<sub>', $title);
    $title = str_replace('</inf>', '</sub>', $title);
    $title = str_replace('<i>', '<em>', $title);
    $title = str_replace('</i>', '</em>', $title);
    $title = htmlspecialchars($title);
    
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