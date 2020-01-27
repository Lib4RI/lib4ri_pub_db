<?php

/**
 * Implements hook_form().
 */
function lib4ri_pub_db_admin_form() {
    $form = array(
        'lib4ri_pub_tabs' => array(
            '#type' => 'vertical_tabs',
            'lib4ri_pub_gen' => array(
                '#type' => 'fieldset',
                '#title' => t('General config'),
                ),
            'lib4ri_pub_scopus' => array(
                '#type' => 'fieldset',
                '#title' => t('Scopus config'),
            ),
            'lib4ri_pub_xref' => array(
                '#type' => 'fieldset',
                '#title' => t('Crossref config'),
            ),
                'lib4ri_pub_auth' => array(
                '#type' => 'fieldset',
                '#title' => t('Authors data'),
            ),
                'lib4ri_pub_journ' => array(
                '#type' => 'fieldset',
                '#title' => t('Journal data'),
            ),
            'lib4ri_pub_title' => array(
                '#type' => 'fieldset',
                '#title' => t('Title data'),
            ),
            'lib4ri_pub_abstr' => array(
                '#type' => 'fieldset',
                '#title' => t('Abstract data'),
            ),
         )
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_scopus']['lib4ri_pub_db_scopus_use'] = array(
        '#type' => 'checkbox',
        '#title' => t('Fetch data from Scopus'),
        '#default_value' => variable_get('lib4ri_pub_db_scopus_use', ''),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_scopus']['lib4ri_pub_db_scopus_api_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Scopus API key'),
        '#default_value' => variable_get('lib4ri_pub_db_scopus_api_key', ''),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_scopus']['lib4ri_pub_db_scopus_data_class'] = array(
        '#type' => 'textfield',
        '#title' => t('Class name for data fetching from Scopus'),
        '#default_value' => variable_get('lib4ri_pub_db_scopus_data_class', ''),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_scopus']['lib4ri_pub_db_scopus_affil_ids'] = array(
        '#type' => 'textfield',
        '#title' => t('Lib4RI authors affiliation codes'),
        '#default_value' => variable_get('lib4ri_pub_db_scopus_affil_ids', ''),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_xref']['lib4ri_pub_db_xref_use'] = array(
        '#type' => 'checkbox',
        '#title' => t('Fetch data from Crossref'),
        '#default_value' => variable_get('lib4ri_pub_db_xref_use', ''),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_xref']['lib4ri_pub_db_xref_pid'] = array(
        '#type' => 'textfield',
        '#title' => t('Crossref PID'),
        '#default_value' => variable_get('lib4ri_pub_db_xref_pid', ''),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_xref']['lib4ri_pub_db_xref_data_class'] = array(
        '#type' => 'textfield',
        '#title' => t('Class name for data fetching from Xref'),
        '#default_value' => variable_get('lib4ri_pub_db_xref_data_class', ''),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_gen']['lib4ri_pub_db_search_collections'] = array(
        '#type' => 'textfield',
        '#title' => t('Collections to search for existing publications'),
        '#default_value' => variable_get('lib4ri_pub_db_search_collections', ''),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_gen']['lib4ri_pub_db_excl_collections'] = array(
        '#type' => 'textfield',
        '#title' => t('Do not use this module for the following collections'),
        '#default_value' => variable_get('lib4ri_pub_db_excl_collections', ''),
        '#required' => FALSE,
    );    
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_gen']['lib4ri_pub_db_journal_enrich_class'] = array(
        '#type' => 'textfield',
        '#title' => t('Class name for journal articles data enrichment'),
        '#default_value' => variable_get('lib4ri_pub_db_journal_enrich_class', ''),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_gen']['lib4ri_pub_db_proceedings_enrich_class'] = array(
        '#type' => 'textfield',
        '#title' => t('Class name for proceedings papers data enrichment'),
        '#default_value' => variable_get('lib4ri_pub_db_proceedings_enrich_class', ''),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_auth_flag'] = array(
        '#type' => 'checkbox',
        '#default_value' => variable_get('lib4ri_pub_db_auth_affil_fetch', TRUE),
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

    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_group_current_solr_search_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Group current name solr search field'),
        '#default_value' => variable_get('lib4ri_pub_db_group_current_solr_search_field', ''),
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

    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_auth_xpath_query'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH author query'),
        '#default_value' => variable_get('lib4ri_pub_db_auth_xpath_query', ''),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_auth_th'] = array(
        '#type' => 'textfield',
        '#title' => t('Threshold for authors decimation (many authors)'),
        '#default_value' => variable_get('lib4ri_pub_db_auth_th', '50'),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_auth_first'] = array(
        '#type' => 'textfield',
        '#title' => t('Number of "first" authors (many authors)'),
        '#default_value' => variable_get('lib4ri_pub_db_auth_first', '10'),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_auth_last'] = array(
        '#type' => 'textfield',
        '#title' => t('Number of "last" authors (many authors)'),
        '#default_value' => variable_get('lib4ri_pub_db_auth_last', '1'),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_journ_flag'] = array(
        '#type' => 'checkbox',
        '#default_value' => variable_get('lib4ri_pub_db_journal_data_fetch', TRUE),
        '#title' => t('Attempt to fetch journal data from DORA'),
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_journ_title_xpath_query'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH journal title query'),
        '#default_value' => variable_get('lib4ri_pub_db_journ_title_xpath_query', "//mods:mods/mods:relatedItem [@type=\"host\"]/mods:titleInfo/mods:title"),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_abbr_title_xpath_query'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH journal abbreviated title query'),
        '#default_value' => variable_get('lib4ri_pub_db_abbr_title_xpath_query', "//mods:mods/mods:relatedItem [@type=\"host\"]/mods:titleInfo [@type=\"abbreviated\"]/mods:title"),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_journ_publish_xpath_query'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH journal publisher query'),
        '#default_value' => variable_get('llib4ri_pub_db_journ_publish_xpath_query', "//mods:mods/mods:relatedItem [@type=\"host\"]/mods:originInfo/mods:publisher"),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_journ_issn_xpath_query'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH journal ISSN query'),
        '#default_value' => variable_get('lib4ri_pub_db_journ_issn_xpath_query', "//mods:mods/mods:relatedItem [@type=\"host\"]/mods:identifier [@type=\"issn\"]"),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_journ_eissn_xpath_query'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH journal e-ISSN query'),
        '#default_value' => variable_get('lib4ri_pub_db_journ_eissn_xpath_query', "//mods:mods/mods:relatedItem [@type=\"host\"]/mods:identifier [@type=\"e-issn\"]"),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_journ_id_xpath_query'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH journal ID query'),
        '#default_value' => variable_get('lib4ri_pub_db_journ_id_xpath_query', "//mods:mods/mods:relatedItem [@type=\"host\"]/mods:identifier [@type=\"journal id\"]"),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_journ_title_solr_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Journal abbreviated title Solr field'),
        '#default_value' => variable_get('lib4ri_pub_db_journ_title_solr_field', 'mods_titleInfo_title_mt'),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_abbr_title_solr_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Journal abbreviated title Solr field'),
        '#default_value' => variable_get('lib4ri_pub_db_abbr_title_solr_field', 'mods_titleInfo_abbreviated_title_mt'),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_journ_publish_solr_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Journal publisher Solr field'),
        '#default_value' => variable_get('lib4ri_pub_db_journ_publish_solr_field', 'mods_originInfo_publisher_mt'),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_journ_issn_solr_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Journal ISSN Solr field'),
        '#default_value' => variable_get('lib4ri_pub_db_journ_issn_solr_field', 'mods_identifier_issn_mt'),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_journ']['lib4ri_pub_db_journ_eissn_solr_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Journal e-ISSN Solr field'),
        '#default_value' => variable_get('lib4ri_pub_db_journ_eissn_solr_field', 'mods_identifier_e-issn_mt'),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_journ_flag"]' => array('checked' => TRUE),
            ),
        ),
    );

//     $form['lib4ri_pub_tabs']['lib4ri_pub_abstr']['lib4ri_pub_db_abstr_tags'] = array(
//         '#type' => 'textfield',
//         '#title' => t('Allowed html tags in abstract'),
//         '#default_value' => variable_get('lib4ri_pub_db_abstr_tags', '<sup><inf><i><sub><em>'),
//         '#required' => false,
//     );

    
//     $form['lib4ri_pub_tabs']['lib4ri_pub_title']['lib4ri_pub_db_title_tags'] = array(
//         '#type' => 'textfield',
//         '#title' => t('Allowed html tags in title'),
//         '#default_value' => variable_get('lib4ri_pub_db_title_tags', '<sup><inf><i><sub><em>'),
//         '#required' => false,
//     );
    
    return system_settings_form($form);
}