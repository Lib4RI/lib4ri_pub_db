<?php 

class Lib4riMetaDataIntegrator{
    
    private $authors = array(); //DOM element?
    
    /**
     * Constructor
     */
    public function __construct() {
        
    }
    
    protected function matchAuthor(){
        
    }
    
    protected function getInternalAffiliation(){
        
    }
    
}

class EawagMetaDataIntegrator extends Lib4riMetaDataIntegrator{
    
}

class EmpaMetaDataIntegrator extends Lib4riMetaDataIntegrator{
    
}

class WslMetaDataIntegrator extends Lib4riMetaDataIntegrator{
    
}

class PsiMetaDataIntegrator extends Lib4riMetaDataIntegrator{
    
}



/******************************************************************************
 * Classes for metadata enrichment
 *****************************************************************************/

/**
 * Generic class to enrich metadata with Lib4ri data
 */

class Lib4riMetaDataEnricher{
    
    protected $dom;
    
    /**
     * Constructor.
     */
    
    public function __construct() {
        
    }
    
    public function setDom($dom){
        $this->dom = $dom;
        return $this;
    }
    
    public function addAffiliation(){
        
        $family_name_search = variable_get('');
        $given_name_search = variable_get(''); //configurable search field
        
        $namespace = variable_get(''); //configurable namespace
        
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
        $qp->solrParams['fl'] = 'PID, '.variable_get('lib4ri_psi_authors_std_name_solr_search_field').','.variable_get('lib4ri_psi_authors_group_name_solr_search_field');
        $qp->solrParams['fq'] = array();
        $qp->solrParams['fq'][] = 'PID:'.$namespace.'*\\:*';
        $qp->executeQuery(FALSE, TRUE);
        
        $output = array();
        $ii = 0;
        
        foreach ($qp->islandoraSolrResult['response']['objects'] as $object) {
            $doc = $object['solr_doc'];
            $group = $doc[variable_get('lib4ri_psi_authors_group_name_solr_search_field')][0];
            $std_name = $doc[variable_get('lib4ri_psi_authors_std_name_solr_search_field')][0];
            $auth_pid = $doc['PID'];
            $ii++;            
        }
        
        if ($ii==1){
            return array('group' => $group, 'std_name' => $std_name, 'pid' => $auth_pid);
        }
        else{
            return $ii;
        }
    }
    
    
}

class EawagMetaDataEnricher extends Lib4riMetaDataEnricher{
    
}

class EmpaMetaDataEnricher extends Lib4riMetaDataEnricher{
    
}

class WslMetaDataEnricher extends Lib4riMetaDataEnricher{
    
}

class PsiMetaDataEnricher extends Lib4riMetaDataEnricher{
    
}