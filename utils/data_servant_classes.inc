<?php 

module_load_include('php', 'publication_DB', 'lib/MetaDataServants');
module_load_include('inc', 'lib4ri_pub_db', 'utils/servant_classes_callbacks');

/**
 * Class to get MODS from DOI using Crossref data
 */
class Lib4riCrossref2ModsServant extends MetaDataServant{
    
    protected $xslt;
    
    /**
     * Constructor.
     */
    public function __construct() {
        $this->fetcher = new CrossrefFetcher();
        $this->processor = new MetaDataProcessor(null);
        
        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_spot_internal_authors_crossref',
            'source' => '',
            'params' => array(
            )
        )
            );
        
        $this->processor->addSteps(array(//'type' => 'callback',
        //                                        'rule' => 'crossref2mods',
        //                                        'source' => '',
            'type' => 'xslt',
//            'rule' => dirname(__FILE__).'/../xslts/psi-journal-article-crossref2mods.xslt',
            'rule' => dirname(__FILE__).'/../xslts/'.$this->xslt,
            'source' => 'file',
            'params' => array('editor' => FALSE,
                'subtitle' => FALSE,
                'publisher' => FALSE)
        )
            );
        
        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_cruch_given_name',
            'source' => '',
            'params' => array(
            )
        )
            );
        
        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_decimate_many_authors',
            'source' => '',
            'params' => array('first' => variable_get('lib4ri_pub_db_auth_first'),
                'last' => variable_get('lib4ri_pub_db_auth_last'),
                'threshold' => variable_get('lib4ri_pub_db_auth_th')
            )
        )
            );
    }
    
    /**
     * Convenience method to set the class specific URL parameter 'pid' (the user's id)
     *
     * @return Crossref2ModsServant
     *   The instatiated class.
     */
    public function setPid($pid){
        $this->fetcher->setPid($pid);
        return $this;
    }
    
    /**
     * Convenience method to set the class specific URL parameter 'doi'
     *
     * @return Crossref2ModsServant
     *   The instatiated class.
     */
    public function setDoi($doi){
        $this->fetcher->setDoi($doi);
        return $this;
    }
}

class Lib4riJournalArticleCrossref2ModsServant extends Lib4riCrossref2ModsServant{
    protected $xslt = 'journal-article-crossref2mods.xslt';
}



class Lib4riProceedingsPaperCrossref2ModsServant extends Lib4riCrossref2ModsServant{
    protected $xslt = 'proceedings-paper-crossref2mods.xslt';
    
    public function __construct()
    {
        parent::__construct();
        
        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_crunch_confdate',
            'source' => '',
            'params' => array(
            )
        )
            );
    }
}

class PsiProceedingsPaperCrossref2ModsServant extends Lib4riProceedingsPaperCrossref2ModsServant{
    protected $xslt = 'psi-proceedings-paper-crossref2mods.xslt';
}

/**
 * Class to get MODS from DOI using Scopus data
 */
class Lib4riScopus2ModsServant extends MetaDataServant{
    
    protected $xslt;
    /**
     * Constructor.
     */
    public function __construct() {
        $this->fetcher = new ScopusAbstractFetcher();
        $this->processor = new MetaDataProcessor(null);

        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_crunch_title',
            'source' => '',
            'params' => array(
            )
        )
            );
        
        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_crunch_abstract',
            'source' => '',
            'params' => array(
            )
        )
            );

        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_spot_internal_authors',
            'source' => '',
            'params' => array(
            )
        )
            );

        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_crunch_keywords',
            'source' => '',
            'params' => array(
            )
        )
            );
        
        $this->processor->addSteps(array('type' => 'xslt',
//            'rule' => dirname(__FILE__).'/../xslts/psi-journal-article-scopus2mods.xslt',
            'rule' => dirname(__FILE__).'/../xslts/'.$this->xslt,
            'source' => 'file',
            'params' => array('editor' => FALSE,
                'subtitle' => FALSE,
                'publisher' => FALSE)
        )
            );
        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_cruch_given_name',
            'source' => '',
            'params' => array(
            )
        )
            );
        
        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_decimate_many_authors',
            'source' => '',
            'params' => array('first' => variable_get('lib4ri_pub_db_auth_first'),
                'last' => variable_get('lib4ri_pub_db_auth_last'),
                'threshold' => variable_get('lib4ri_pub_db_auth_th')
            )
        )
            );
    }
    
    /**
     * Convenience method to set the class specific URL parameter 'key'
     *
     * @return Scopus2ModsServant
     *   The instatiated class.
     */
    public function setKey($pid){
        $this->fetcher->setKey($pid);
        return $this;
    }
    
    /**
     * Convenience method to set the class specific URL parameter 'doi'
     *
     * @return Scopus2ModsServant
     *   The instatiated class.
     */
    public function setDoi($doi){
        $this->fetcher->setDoi($doi);
        return $this;
    }
    
    /**
     * Convenience method to set the class specific URL parameter 'scopusId'
     *
     * @return Scopus2ModsServant
     *   The instatiated class.
     */
    public function setScopusId($scopus_id){
        $this->fetcher->setScopusId($scopus_id);
        return $this;
    }
    
    /**
     * Convenience method to set the class specific URL parameter 'eid'
     *
     * @return Scopus2ModsServant
     *   The instatiated class.
     */
    public function setEid($eid){
        $this->fetcher->setEid($eid);
        return $this;
    }
    
    /**
     * Convenience method to set the class specific URL parameter 'pubmed_id'
     *
     * @return Scopus2ModsServant
     *   The instatiated class.
     */
    public function setPmid($Pmid){
        $this->fetcher->setPmid($Pmid);
        return $this;
    }
    
}

class Lib4riJournalArticleScopus2ModsServant extends Lib4riScopus2ModsServant{
    protected $xslt = 'journal-article-scopus2mods.xslt';
}

class Lib4riProceedingsPaperScopus2ModsServant extends Lib4riScopus2ModsServant{
    protected $xslt = 'proceedings-paper-scopus2mods.xslt';
    
    public function __construct()
    {
        parent::__construct();
        
        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_crunch_confdate',
            'source' => '',
            'params' => array(
                )
            )
        );
    }
}

class PsiProceedingsPaperScopus2ModsServant extends Lib4riProceedingsPaperScopus2ModsServant{
    protected $xslt = 'psi-proceedings-paper-scopus2mods.xslt';
}

class Lib4riDataCiteDoisServant extends DataCiteDoisServant{
    /**
     * Constructor.
     */
    public function __construct() {
        parent::__construct();
        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_res_data_filter_relation_type',
            'source' => '',
            'params' => array(
                )  
            )
        );
        $this->processor->addSteps(array('type' => 'callback',
            'rule' => 'lib4ri_pub_db_res_data_filter_publisher',
            'source' => '',
            'params' => array(
                )
            )
        );
        
    }
}