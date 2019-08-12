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
    protected $sections;
    
    /**
     * Constructor.
     */
    
    public function __construct() {
        
    }
    
    public function setDom($dom){
        $this->dom = $dom;
        return $this;
    }
    
    public function getAuthSections(){
        $this->xpath = new DOMXPath($this->dom);
        $this->sections = $this->xpath->query("//mods:mods/mods:name [@type=\"personal\"]");
        
        return $this;
    }
    
    public function addStdName(){
        module_load_include('inc', 'lib4ri_pub_db', 'includes/functions');
        
         $this->xpath = new DOMXPath($this->dom);
         $sections = $this->xpath->query("//mods:mods/mods:name [@type=\"personal\"]");
        foreach ($sections as $section){
            unset($affil_data);
            $fourri_node = $section->getElementsByTagName('fourri')[0];
            $fourri = $fourri_node->nodeValue;
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
                
                $affil_search = 1;
                $auth_data = get_authors_data_from_name($g_name, $f_name);
                
                if (sizeof($auth_data) > 1){
                    $auth_data[0]['std_name'] = '4RI author. Multiple matches.';
                    $auth_data[0]['pid'] = '';
                    $affil_search = 0;
                }
                if (sizeof($auth_data) == 0){
                    $auth_data[0]['std_name'] = '4RI author. No matches.';
                    $auth_data[0]['pid'] = '';
                    $affil_search = 0;
                }
                                
                $elemU = $this->dom->createElement('alternativeName');
                $elemU->setAttribute('altType','formal_name');
                
                $elem = $this->dom->createElement('namePart',$auth_data[0]['std_name']);
//                $elem->setAttribute('type','group');
                $elem2 = $this->dom->createElement('nameIdentifier',$auth_data[0]['pid']);
                $elem2->setAttribute('type','authorId');
                
                $elemU->appendChild($elem);
                $elemU->appendChild($elem2);
                $section->appendChild($elemU);
                
                if ($affil_search){
                    $affil_data = get_authors_affiliation_from_aff_name($auth_data[0]['group']);
                    $unit_id = get_authors_unit_from_aff_name($auth_data[0]['group'])[0]['g_pid'];
                    
                    $elem_uid = $this->dom->createElement('nameIdentifier',$unit_id);
                    $elem_uid->setAttribute('type','organizational unit id');
                    $section->appendChild($elem_uid);
                    
                    $elem_group = $this->dom->createElement('affiliation',$auth_data[0]['group']);
                    $elem_group->setAttribute('type','group');
                    $section->appendChild($elem_group);
                    
                    $elem_section = $this->dom->createElement('affiliation',$affil_data->s_name);
                    $elem_section->setAttribute('type','section');
                    $section->appendChild($elem_section);
                    
                    $elem_department = $this->dom->createElement('affiliation',$affil_data->l_name);
                    $elem_department->setAttribute('type','department');
                    $section->appendChild($elem_department);

                    $elem_division = $this->dom->createElement('affiliation',$affil_data->d_name);
                    $elem_division->setAttribute('type','division');
                    $section->appendChild($elem_division);
                }
                
                $section->removeChild($fourri_node);
            }
            
        }
        return $this;
    }
    
    public function addAffiliation(){
        foreach ($this->sections as $section){
            
        }
    }
    
    public function removeFourriTag(){
        foreach ($this->sections as $section){
            $fourri_node = $section->getElementsByTagName('fourri')[0];
            $section->removeChild($fourri_node);
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