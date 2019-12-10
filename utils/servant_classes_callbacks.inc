<?php 

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
    module_load_include('inc', 'lib4ridora', 'includes/utilities.author');
    $xpath = new DOMXPath($dom);
    $authors = $xpath->query(variable_get('lib4ri_pub_db_auth_xpath_query'));
    
    foreach ($authors as $author){
        $name_parts = $author->getElementsByTagName('namePart');
        foreach ($name_parts as $name_part){
            if ($name_part->getAttribute('type')=='given'){
                $name_part->nodeValue = lib4ridora_unspace_name_given($name_part->nodeValue);
            }
        }
    }
    return $dom;
}
