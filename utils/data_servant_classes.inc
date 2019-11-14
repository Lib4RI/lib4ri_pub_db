<?php 

module_load_include('php', 'publication_DB', 'lib/MetaDataServants');


/**
 * Class to get MODS from DOI using Crossref data
 */
class PsiCrossref2ModsServant extends MetaDataServant{
    
    /**
     * Constructor.
     */
    public function __construct() {
        $this->fetcher = new CrossrefFetcher();
        $this->processor = new MetaDataProcessor(null);
        $this->processor->addSteps(array(//'type' => 'callback',
        //                                        'rule' => 'crossref2mods',
        //                                        'source' => '',
            'type' => 'xslt',
            'rule' => dirname(__FILE__).'/../xslts/psi-journal-article-crossref2mods.xslt',
            'source' => 'file',
            'params' => array('editor' => FALSE,
                'subtitle' => FALSE,
                'publisher' => FALSE)
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

/**
 * Class to get MODS from DOI using Scopus data
 */
class PsiScopus2ModsServant extends MetaDataServant{
    
    /**
     * Constructor.
     */
    public function __construct() {
        $this->fetcher = new ScopusAbstractFetcher();
        $this->processor = new MetaDataProcessor(null);
        $this->processor->addSteps(array('type' => 'xslt',
            'rule' => dirname(__FILE__).'/../xslts/psi-journal-article-scopus2mods.xslt',
            'source' => 'file',
            'params' => array('editor' => FALSE,
                'subtitle' => FALSE,
                'publisher' => FALSE)
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
