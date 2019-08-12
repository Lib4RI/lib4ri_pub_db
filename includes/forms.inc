<?php

/**
 * Implements hook_form().
 */
function lib4ri_pub_db_admin_form() {
    $form = array(
        'lib4ri_pub_tabs' => array(
            '#type' => 'vertical_tabs',
                'lib4ri_pub_auth' => array(
                '#type' => 'fieldset',
                '#title' => t('Authors data'),
                ),
                'lib4ri_pub_b' => array(
                '#type' => 'fieldset',
                '#title' => t('---'),
            )
            
         )
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_auth_flag'] = array(
        '#type' => 'checkbox',
        '#default_value' => variable_get('lib4ri_staged_ingest_pdfa_at_unstage', TRUE),
        '#title' => t('Attempt to add internal authors affiliation'),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_given_name_solr_search_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Given name Solr search field'),
        '#default_value' => variable_get('lib4ri_pub_db_given_name_solr_search_field', ''),
        '#required' => FALSE,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_family_name_solr_search_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Family name Solr search field'),
        '#default_value' => variable_get('lib4ri_pub_db_family_name_solr_search_field', ''),
        '#required' => TRUE,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_group_name_solr_search_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Group name Solr search field'),
        '#default_value' => variable_get('lib4ri_pub_db_group_name_solr_search_field', ''),
        '#required' => TRUE,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_group_id_solr_search_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Group ID solr search field'),
        '#default_value' => variable_get('lib4ri_pub_db_group_id_solr_search_field', ''),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_std_name_solr_search_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Standard form of name Solr search field'),
        '#default_value' => variable_get('lib4ri_pub_db_std_name_solr_search_field', ''),
        '#required' => TRUE,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_solr_namespace'] = array(
        '#type' => 'textfield',
        '#title' => t('Solr query namespace restriction'),
        '#default_value' => variable_get('lib4ri_pub_db_solr_namespace', ''),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
        
    return system_settings_form($form);
}