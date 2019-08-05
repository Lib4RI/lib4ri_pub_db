<?php

function get_authors_data_from_name($g_name, $f_name){
    $family_name_search = variable_get('lib4ri_pub_db_family_name_solr_search_field');
    $given_name_search = variable_get('lib4ri_pub_db_given_name_solr_search_field'); //configurable search field
    
    $g_name = str_replace ('.', '', $g_name);
    
    $namespace = variable_get('lib4ri_pub_db_solr_namespace'); //configurable namespace
        
    module_load_include('inc', 'islandora_solr', 'includes/utilities');
    module_load_include('inc', 'lib4ri_psi_authors', 'includes/queries');
    
    $qp = new IslandoraSolrQueryProcessor();
    if ($given_name_search){
        $qp->buildQuery(format_string('!field1:(!value1*) AND !field2:(!value2*)', array(
            '!field1' => islandora_solr_lesser_escape($family_name_search),
            '!value1' => $f_name,
            '!field2' => islandora_solr_lesser_escape($given_name_search),
            '!value2' => $g_name,
        )));
        
    }
    else{
        $qp->buildQuery(format_string('!field:(!value)', array(
            '!field' => islandora_solr_lesser_escape($family_name_search),
            '!value' => $f_name.'*'.$g_name.'*',
        )));
        
    }
    $qp->solrParams['fl'] = 'PID, '.variable_get('lib4ri_pub_db_std_name_solr_search_field').','.variable_get('lib4ri_pub_db_group_name_solr_search_field');
    $qp->solrParams['fq'] = array();
    $qp->solrParams['fq'][] = 'PID:'.$namespace.'*\\:*';
    $qp->executeQuery(FALSE, TRUE);
    
    $output = array();
    $ii = 0;
    
    $ret = [];
    
    foreach ($qp->islandoraSolrResult['response']['objects'] as $object) {
        $doc = $object['solr_doc'];
        $group = $doc[variable_get('lib4ri_pub_db_group_name_solr_search_field')][0];
        $std_name = $doc[variable_get('lib4ri_pub_db_std_name_solr_search_field')][0];
        $auth_pid = $doc['PID'];
        array_push($ret, array('group' => $group, 'std_name' => $std_name, 'pid' => $auth_pid));
        $ii++;
    }
    
//     if ($ii==1){
//         return array('group' => $group, 'std_name' => $std_name, 'pid' => $auth_pid);
//     }
//     else{
//         return $ii;
//     }

    return $ret;
}

function get_authors_affiliation_from_pid($pid){
    
}