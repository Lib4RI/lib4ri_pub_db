<?php
define('LIB4RI_PSI_AUTHORS_GROUPS_TABLE', 'lib4ri_psi_authors_groups');
define('LIB4RI_PSI_AUTHORS_SECTIONS_TABLE', 'lib4ri_psi_authors_sections');
define('LIB4RI_PSI_AUTHORS_DEPARTMENTS_TABLE', 'lib4ri_psi_authors_departments');
define('LIB4RI_PSI_AUTHORS_DIVISIONS_TABLE', 'lib4ri_psi_authors_divisions');


function get_authors_data_from_name($g_name, $f_name){
    $family_name_search = variable_get('lib4ri_pub_db_family_name_solr_search_field');
    $given_name_search = variable_get('lib4ri_pub_db_given_name_solr_search_field'); //configurable search field
    
    //$g_name = str_replace ('.', '', $g_name);
    $g_name = trim($g_name)[0];
    
    $namespace = variable_get('lib4ri_pub_db_solr_namespace'); //configurable namespace
        
    module_load_include('inc', 'islandora_solr', 'includes/utilities');
//    module_load_include('inc', 'lib4ri_psi_authors', 'includes/queries');
    
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
function get_authors_unit_from_aff_name($group){
    $qp = new IslandoraSolrQueryProcessor();
    $qp->buildQuery(format_string('!field:(!value)', array(
        '!field' => islandora_solr_lesser_escape(variable_get('lib4ri_pub_db_group_id_solr_search_field')),
        '!value' => $group,
    )));
    
    $qp->solrParams['fl'] = 'PID, '.variable_get('lib4ri_pub_db_group_current_solr_search_field');
    $qp->solrParams['fq'] = array();
//    $qp->solrParams['fq'][] = 'PID:'.$namespace.'*\\:*';
    $qp->executeQuery(FALSE, TRUE);
    
    $ret = [];
    
    foreach ($qp->islandoraSolrResult['response']['objects'] as $object) {
        $doc = $object['solr_doc'];
        $group_id = $doc['PID'];
        $g_cname = $doc[variable_get('lib4ri_pub_db_std_name_solr_search_field')][0];
        array_push($ret, array('g_pid' => $group_id, 'g_cname' => $g_cname));
    }
    
    return $ret;
}

function get_authors_affiliation_from_aff_name($group){
    $query = db_select(LIB4RI_PSI_AUTHORS_GROUPS_TABLE, 'g');
    $query->condition('g.name',$group);
    $query->addField('g', 'id', 'g_id');
    $query->addField('g', 'section_id', 's_id');
    $query->addField('g', 'department_id', 'l_id');
    $query->addField('g', 'division_id', 'd_id');
    $query->addField('g', 'name', 'g_name');
    
    $res = $query->execute();
    $affils = [];
    foreach ($res as $affil) {
        array_push($affils, $affil);
    }
    $affils[0]->s_name = lib4ri_pub_db_get_section_from_id($affils[0]->s_id);
    $affils[0]->l_name = lib4ri_pub_db_get_department_from_id($affils[0]->l_id);
    $affils[0]->d_name = lib4ri_pub_db_get_division_from_id($affils[0]->d_id);
    return $affils[0];
    
}

function lib4ri_pub_db_get_section_from_id($id){
    $res = db_select(LIB4RI_PSI_AUTHORS_SECTIONS_TABLE, 'f')
    ->fields('f', array('name'))
    ->condition('id', $id)
    ->execute();
    
    foreach ($res as $name) {
        $name = $name->name;
    }
    return $name;
    
}

function lib4ri_pub_db_get_department_from_id($id){
    $res = db_select(LIB4RI_PSI_AUTHORS_DEPARTMENTS_TABLE, 'f')
    ->fields('f', array('name'))
    ->condition('id', $id)
    ->execute();
    
    foreach ($res as $name) {
        $name = $name->name;
    }
    return $name;
    
}

function lib4ri_pub_db_get_division_from_id($id){
    $res = db_select(LIB4RI_PSI_AUTHORS_DIVISIONS_TABLE, 'f')
    ->fields('f', array('name'))
    ->condition('id', $id)
    ->execute();
    
    foreach ($res as $name) {
        $name = $name->name;
    }
    return $name;
    
}
