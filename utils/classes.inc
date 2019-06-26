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