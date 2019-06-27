<?php

/**
 * Implements hook_form().
 */
function lib4ri_pub_db_admin_form() {
    $form['lib4ri_pub_db_given_name_solr_search_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Given name Solr search field'),
        '#default_value' => variable_get('lib4ri_pub_db_given_name_solr_search_field', ''),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_db_family_name_solr_search_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Family name Solr search field'),
        '#default_value' => variable_get('lib4ri_pub_db_family_name_solr_search_field', ''),
        '#required' => TRUE,
    );
    
    $form['lib4ri_pub_db_group_name_solr_search_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Group name Solr search field'),
        '#default_value' => variable_get('lib4ri_pub_db_group_name_solr_search_field', ''),
        '#required' => TRUE,
    );
    
    $form['lib4ri_pub_db_std_name_solr_search_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Standard form of name Solr search field'),
        '#default_value' => variable_get('lib4ri_pub_db_std_name_solr_search_field', ''),
        '#required' => TRUE,
    );
    
    $form['lib4ri_pub_db_solr_namespace'] = array(
        '#type' => 'textfield',
        '#title' => t('Solr query namespace restriction'),
        '#default_value' => variable_get('lib4ri_pub_db_solr_namespace', ''),
        '#required' => false,
    );
        
    return system_settings_form($form);
}