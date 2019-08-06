<?php 

module_load_include('php', 'publication_DB', 'lib/MetaDataServants');

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

class Lib4riMetaDataEnricher extends MetaDataAbstract{
    
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
    
    public function addStdName(){
        module_load_include('inc', 'lib4ri_pub_db', 'includes/functions');
        
        $this->xpath = new DOMXPath($this->dom);
        $sections = $this->xpath->query("//mods:mods/mods:name [@type=\"personal\"]");
        foreach ($sections as $section){
            $fourri = $section->getElementsByTagName('fourri')[0]->nodeValue;
            if ($fourri == 'true'){
                $name_parts = $section->getElementsByTagName('namePart');
                foreach ($name_parts as $name_part){
                   if ($name_part->getAttribute('type')=='family'){
                       $f_name = $name_part->nodeValue;
                   }
                   if ($name_part->getAttribute('type')=='given'){
                       $g_name = $name_part->nodeValue;
                   }
                }
                
                $auth_data = get_authors_data_from_name($g_name, $f_name);
                 
                $elemU = $this->dom->createElement('alternativeName');
                $elemU->setAttribute('altType','formal_name');
                
                $elem = $this->dom->createElement('namePart',$auth_data['std_name']);
//                $elem->setAttribute('type','group');
                $elem2 = $this->dom->createElement('nameIdentifier',$auth_data['pid']);
                $elem2->setAttribute('type','authorId');
                
                $elemU->appendChild($elem);
                $section->appendChild($elemU);
            }
            
        }
        return $this;
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