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
            'lib4ri_pub_conf' => array(
                '#type' => 'fieldset',
                '#title' => t('Conference items data'),
            ),
            'lib4ri_pub_title' => array(
                '#type' => 'fieldset',
                '#title' => t('Title data'),
            ),
            'lib4ri_pub_abstr' => array(
                '#type' => 'fieldset',
                '#title' => t('Abstract data'),
            ),
            'lib4ri_pub_fund' => array(
                '#type' => 'fieldset',
                '#title' => t('Funding data'),
            ),
            'lib4ri_pub_resdata' => array(
                '#type' => 'fieldset',
                '#title' => t('Research data'),
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
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_scopus']['lib4ri_pub_db_scopus_journal_data_class'] = array(
        '#type' => 'textfield',
        '#title' => t('Class name for journal articles data fetching from Scopus'),
        '#default_value' => variable_get('lib4ri_pub_db_scopus_journal_data_class', ''),
        '#required' => FALSE,
    );


    $form['lib4ri_pub_tabs']['lib4ri_pub_scopus']['lib4ri_pub_db_scopus_proceedings_data_class'] = array(
        '#type' => 'textfield',
        '#title' => t('Class name for proceedings papers data fetching from Scopus'),
        '#default_value' => variable_get('lib4ri_pub_db_scopus_proceedings_data_class', ''),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_scopus']['lib4ri_pub_db_scopus_affil_ids'] = array(
        '#type' => 'textfield',
        '#title' => t('Lib4RI authors affiliation codes'),
        '#default_value' => variable_get('lib4ri_pub_db_scopus_affil_ids', ''),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_scopus']['lib4ri_pub_db_kw_lc'] = array(
        '#type' => 'checkbox',
        '#title' => t('Convert keywords to lowercase'),
        '#default_value' => variable_get('lib4ri_pub_db_kw_lc', ''),
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

    $form['lib4ri_pub_tabs']['lib4ri_pub_xref']['lib4ri_pub_db_xref_journal_data_class'] = array(
        '#type' => 'textfield',
        '#title' => t('Class name for journal articles data fetching from Xref'),
        '#default_value' => variable_get('lib4ri_pub_db_xref_journal_data_class', ''),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_xref']['lib4ri_pub_db_xref_proceedings_data_class'] = array(
        '#type' => 'textfield',
        '#title' => t('Class name for proceedings papers data fetching from Xref'),
        '#default_value' => variable_get('lib4ri_pub_db_xref_proceedings_data_class', ''),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_xref']['lib4ri_pub_db_xref_affiliation_strings'] = array(
        '#type' => 'textarea',
        '#title' => t('Lib4RI authors affiliation sub-strings ("|" separated)'),
        '#default_value' => variable_get('lib4ri_pub_db_xref_affiliation_strings', ''),
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
        '#title' => t('Authors Solr query namespace restriction'),
        '#default_value' => variable_get('lib4ri_pub_db_solr_namespace', ''),
        '#required' => false,
        '#states' => array(
            'visible' => array(
                ':input[name="lib4ri_pub_db_auth_flag"]' => array('checked' => TRUE),
            ),
        ),
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_auth']['lib4ri_pub_db_units_solr_namespace'] = array(
        '#type' => 'textfield',
        '#title' => t('Units Solr query namespace restriction'),
        '#default_value' => variable_get('lib4ri_pub_db_units_solr_namespace', ''),
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

    $form['lib4ri_pub_tabs']['lib4ri_pub_conf']['lib4ri_pub_db_conf_date_xpath_query'] = array(
        '#type' => 'textfield',
        '#title' => t('Conference date XPATH query' ),
        '#default_value' => variable_get('lib4ri_pub_db_conf_date_xpath_query', '//mods:mods/mods:originInfo/mods:dateOther [@type="conferenceDate"]'),
        '#required' => true,
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

    $form['lib4ri_pub_tabs']['lib4ri_pub_fund']['lib4ri_pub_db_fund_refs_section_xpath_query'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH Funding references section query'),
        '#default_value' => variable_get('lib4ri_pub_db_fund_refs_section_xpath_query', '//mods:mods/mods:extension/mods:fundingReferences'),
        '#required' => false,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_fund']['lib4ri_pub_db_fund_refs_xpath_query'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH Funding references query'),
        '#default_value' => variable_get('lib4ri_pub_db_fund_refs_xpath_query', '//mods:mods/mods:extension/mods:fundingReferences/mods:fundingReference'),
        '#required' => false,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_fund']['lib4ri_pub_db_funder_tag_name'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS Funder tag name'),
        '#default_value' => variable_get('lib4ri_pub_db_funder_tag_name', 'funderName'),
        '#required' => false,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_fund']['lib4ri_pub_db_fund_id_tag_name'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS Funder ID tag name'),
        '#default_value' => variable_get('lib4ri_pub_db_fund_id_tag_name', 'funderIdentifier'),
        '#required' => false,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_fund']['lib4ri_pub_db_fund_stream_tag_name'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS Funding Stream tag name'),
        '#default_value' => variable_get('lib4ri_pub_db_fund_stream_tag_name', 'fundingStream'),
        '#required' => false,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_fund']['lib4ri_pub_db_fund_title_tag_name'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS Award Title tag name'),
        '#default_value' => variable_get('lib4ri_pub_db_fund_title_tag_name', 'awardTitle'),
        '#required' => false,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_fund']['lib4ri_pub_db_fund_awnum_tag_name'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS Award Number tag name'),
        '#default_value' => variable_get('lib4ri_pub_db_fund_awnum_tag_name', 'awardNumber'),
        '#required' => false,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_fund']['lib4ri_pub_db_fund_snf_id_proc'] = array(
        '#type' => 'checkbox',
        '#title' => t('Attempt SNSF ID extraction'),
        '#default_value' => variable_get('lib4ri_pub_db_fund_snf_id_proc', ''),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_fund']['lib4ri_pub_db_fund_warn_on_mismatch'] = array(
        '#type' => 'checkbox',
        '#title' => t('Raise a warning when no ID match is found'),
        '#default_value' => variable_get('lib4ri_pub_db_fund_warn_on_mismatch', ''),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_enrich_class'] = array(
        '#type' => 'textfield',
        '#title' => t('Research data enrichment class'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_enrich_class', 'DataCiteDoisServant'),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_enrich_relations'] = array(
        '#type' => 'textfield',
        '#title' => t('Research data enrichment - Datacite relation types (comma separated)'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_enrich_relations', 'IsSupplementTo'),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_enrich_excl_relations'] = array(
        '#type' => 'textfield',
        '#title' => t('Research data enrichment - Datacite <i>excluded</i> relation types (comma separated)'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_enrich_excl_relations', 'IsObsoletedBy, IsPartOf'),
        '#required' => FALSE,
    );
    
//     $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_enrich_publishers'] = array(
//         '#type' => 'textarea',
//         '#title' => t('Research data enrichment - Datacite publishers (one per line)'),
//         '#default_value' => variable_get('lib4ri_pub_db_resdata_enrich_publishers', ''),
//         '#required' => FALSE,
//     );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_enrich_publishers_conf'] = array(
        '#type' => 'markup',
        '#markup' => t('<a href="config/publishers">Research data enrichment - Publishers configuration</a>'),
    );
    
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_section'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH research data section query'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_section', '//mods:mods/mods:relatedItem [@type="otherType"]'),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_section_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Research data section name'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_section_name', 'relatedItem'),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_section_attribute_label'] = array(
        '#type' => 'textfield',
        '#title' => t('Research data section attribute label'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_section_attribute_label', 'type'),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_section_attribute_value'] = array(
        '#type' => 'textfield',
        '#title' => t('Research data section attribute value'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_section_attribute_value', 'otherType'),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_tag'] = array(
        '#type' => 'textfield',
        '#title' => t('MODS XPATH research data tag sub-query'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_tag', '/mods:identifier [@type="uri"]'),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_tag_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Research data tag name'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_tag_name', 'identifier'),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_tag_attribute_label'] = array(
        '#type' => 'textfield',
        '#title' => t('Research data tag attribute label'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_tag_attribute_label', 'type'),
        '#required' => FALSE,
    );
    
    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_tag_attribute_value'] = array(
        '#type' => 'textfield',
        '#title' => t('Research data tag attribute value'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_tag_attribute_value', 'uri'),
        '#required' => FALSE,
    );

    $form['lib4ri_pub_tabs']['lib4ri_pub_resdata']['lib4ri_pub_db_resdata_solr_doi_field'] = array(
        '#type' => 'textfield',
        '#title' => t('Research data tag attribute value'),
        '#default_value' => variable_get('lib4ri_pub_db_resdata_solr_doi_field', 'mods_identifier_doi_ms'),
        '#required' => FALSE,
    );
    
    return system_settings_form($form);
}

function lib4ri_pub_db_data_publishers_form() {
    $form = [];
    return $form;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */

function lib4ri_pub_db_form_lib4ri_pub_db_data_publishers_form_alter(&$form, &$form_state) {
    //     $form = [];
    //     return $form;
    module_load_include('inc', 'lib4ri_pub_db', 'includes/functions');
    $publishers = lib4ri_pub_db_get_data_publishers();
    
    foreach ($publishers as $publisher){
        $form[$publisher->id.'_set'] = array(
            '#title' => t($publisher->label),
            '#type' => 'fieldset',
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
        );
        $form[$publisher->id.'_set'][$publisher->id.'_label'] = array(
            '#title' => t('Label'),
            '#default_value' => t($publisher->label),
            '#type' => 'textfield',
        );
        $form[$publisher->id.'_set'][$publisher->id.'_publisher_string'] = array(
            '#title' => t('Publisher string'),
            '#default_value' => t($publisher->publisher_string),
            '#type' => 'textfield',
        );
        $form[$publisher->id.'_set'][$publisher->id.'_allowed_rel_types'] = array(
            '#title' => t('Allowed relation types'),
            '#default_value' => t($publisher->allowed_rel_types),
            '#type' => 'textfield',
        );
        $form[$publisher->id.'_set'][$publisher->id.'_forbidden_rel_types'] = array(
            '#title' => t('Excluded relation types'),
            '#default_value' => t($publisher->forbidden_rel_types),
            '#type' => 'textfield',
        );
        $form[$publisher->id.'_set'][$publisher->id.'_function'] = array(
            '#title' => t('Additional processing function'),
            '#default_value' => t($publisher->function),
            '#type' => 'textfield',
        );
        $form[$publisher->id.'_set'][$publisher->id.'_active'] = array(
            '#title' => t('Active'),
            '#default_value' => $publisher->active,
            '#type' => 'checkbox',
        );
        $form[$publisher->id.'_set'][$publisher->id.'_update'] = array(
            '#name' => $publisher->id.'_update',
            '#type' => 'submit',
            '#value' => t('Update'),
        );
        $form[$publisher->id.'_set'][$publisher->id.'_delete'] = array(
            '#name' => $publisher->id.'_delete',
            '#type' => 'submit',
            '#value' => t('Delete'),
        );
    }
    /****************************************************************************/
    $form['new_set'] = array(
        '#title' => t('Insert a new publisher'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );
    
    $form['new_set']['new_label'] = array(
        '#title' => t('Label'),
        '#default_value' => '',
        '#type' => 'textfield',
        '#required' => FALSE,
    );
    
    $form['new_set']['new_publisher_string'] = array(
        '#title' => t('Publisher string'),
        '#default_value' => '',
        '#type' => 'textfield',
    );
    $form['new_set']['new_allowed_rel_types'] = array(
        '#title' => t('Allowed relation types'),
        '#default_value' => '',
        '#type' => 'textfield',
    );
    $form['new_set']['new_forbidden_rel_types'] = array(
        '#title' => t('Excluded relation types'),
        '#default_value' => '',
        '#type' => 'textfield',
    );
    $form['new_set']['new_function'] = array(
        '#title' => t('Additional processing function'),
        '#default_value' => '',
        '#type' => 'textfield',
    );
    $form['new_set']['new_active'] = array(
        '#title' => t('Active'),
        '#default_value' => '1',
        '#type' => 'checkbox',
    );
    $form['new_set']['insert_new'] = array(
        '#type' => 'submit',
        '#value' => t('Insert'),
    );
    
    return $form;
}

function lib4ri_pub_db_data_publishers_form_validate($form, &$form_state) {
    if (empty($form_state['values']['new_label']) && ($form_state['clicked_button']['#parents'][0] == 'insert_new')){
        form_set_error('new_label', t('Label is required'));
    }
    if (empty($form_state['values']['new_publisher_string']) && ($form_state['clicked_button']['#parents'][0] == 'insert_new')){
        form_set_error('new_publisher_string', t('Publisher string is required'));
    }
    
}

function lib4ri_pub_db_data_publishers_form_submit(&$form, &$form_state) {
    module_load_include('inc', 'protein_db', 'includes/queries');
    
    if ($form_state['clicked_button']['#parents'][0] == 'insert_new'){
        lib4ri_pub_db_insert_data_publisher(array('id' => $form_state['values']['new_id'],
            'label' => $form_state['values']['new_label'],
            'publisher_string' => $form_state['values']['new_publisher_string'],
            'allowed_rel_types' => $form_state['values']['new_allowed_rel_types'],
            'forbidden_rel_types' => $form_state['values']['new_forbidden_rel_types'],
            'function' => $form_state['values']['new_function'],
            'active' => $form_state['values']['new_active'],
        ));
    }
    
    if (strpos($form_state['clicked_button']['#parents'][0], '_delete') !== false) {
        $id = str_replace('_delete', '', $form_state['clicked_button']['#parents'][0]);
        lib4ri_pub_db_delete_data_publisher($id);
    }
    
    if (strpos($form_state['clicked_button']['#parents'][0], '_update') !== false) {
        $id = str_replace('_update', '', $form_state['clicked_button']['#parents'][0]);
        lib4ri_pub_db_update_data_publisher(array(
            'id' => $id,
            'label' => $form_state['values'][$id.'_label'],
            'publisher_string' => $form_state['values'][$id.'_publisher_string'],
            'allowed_rel_types' => $form_state['values'][$id.'_allowed_rel_types'],
            'forbidden_rel_types' => $form_state['values'][$id.'_forbidden_rel_types'],
            'function' => $form_state['values'][$id.'_function'],
            'active' => $form_state['values'][$id.'_active'],
        ));
    }
    
    
    //     drupal_set_message(t($message));
}
