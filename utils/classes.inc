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
    protected $messages = [];
    protected $ids = [];
    
    /**
     * Constructor.
     */
    
    public function __construct() {
    
    }
    
    public function enrich(){
        $this->addStdName();
        $this->checkJournal();
    }
    
    public function setIds($ids){
        $this->ids = $ids;
    }
    
    protected function setMessage($message, $type = 'status'){
        array_push($this->messages, array('message' => $message, 'type' => $type));
    }
    
    public function getMessages(){
        return $this->messages;
    }
    
    public function setDom($dom){
        $this->dom = $dom;
        return $this;
    }
    
    public function getAuthSections(){
        $this->xpath = new DOMXPath($this->dom);
        $this->sections = $this->xpath->query(variable_get('lib4ri_pub_db_auth_xpath_query'));
        
        return $this;
    }
    
    public function addStdName(){
        module_load_include('inc', 'lib4ri_pub_db', 'includes/functions');
        
         $this->xpath = new DOMXPath($this->dom);
         $sections = $this->xpath->query(variable_get('lib4ri_pub_db_auth_xpath_query'));
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
                    $this->setMessage('Multiple matches for auhor '.$g_name.' '.$f_name, 'warning');
                }
                if (sizeof($auth_data) == 0){
                    $auth_data[0]['std_name'] = '4RI author. No matches.';
                    $auth_data[0]['pid'] = '';
                    $affil_search = 0;
                    $this->setMessage('No matches for auhor '.$g_name.' '.$f_name, 'warning');
                }
                                                
                $elem = $this->dom->createElement('fullName',$auth_data[0]['std_name']);
                $elem2 = $this->dom->createElement('nameIdentifier',$auth_data[0]['pid']);
                $elem2->setAttribute('type','authorId');
                
                $section->appendChild($elem);
                $section->appendChild($elem2);
                
                if ($affil_search){
                    $unit_data = get_authors_unit_from_aff_name($auth_data[0]['group'])[0];
                    $unit_id = $unit_data['g_pid'];
                    $unit_name = $unit_data['g_cname'];
                    
                    $elem_uid = $this->dom->createElement('nameIdentifier',$unit_id);
                    $elem_uid->setAttribute('type','organizational unit id');
                    $section->appendChild($elem_uid);
                    
                    $elem_group = $this->dom->createElement('affiliation',$unit_name);
//                    $elem_group->setAttribute('type','group');
                    $section->appendChild($elem_group);
                }
                
                $section->removeChild($fourri_node);
            }
            
        }
        return $this;
    }
    
    public function checkJournal(){
        $this->xpath = new DOMXPath($this->dom);

        $title_node = $this->xpath->query(variable_get('lib4ri_pub_db_journ_title_xpath_query'))[0];
        $title = $title_node->nodeValue;
        
        $abbrev_title = $this->xpath->query(variable_get('lib4ri_pub_db_abbr_title_xpath_query'))[0];
        $publisher = $this->xpath->query(variable_get('lib4ri_pub_db_journ_publish_xpath_query'))[0];
        $issn = $this->xpath->query(variable_get('lib4ri_pub_db_journ_issn_xpath_query'))[0];
        $e_issn = $this->xpath->query(variable_get('lib4ri_pub_db_journ_eissn_xpath_query'))[0];
        $id = $this->xpath->query(variable_get('lib4ri_pub_db_journ_id_xpath_query'))[0];
        
        $qp = new IslandoraSolrQueryProcessor();
//         $qp->buildQuery(format_string('!field:(!value)', array(
//             '!field' => islandora_solr_lesser_escape("mods_titleInfo_title_mt"),
//             '!value' => $title,
//         )));
        
        $s_issn = str_replace('-','',$issn->nodeValue);
        $s_issn = substr($s_issn,0,4).'-'.substr($s_issn,4,4);
        $s_e_issn = str_replace('-','',$e_issn->nodeValue);
        $s_e_issn = substr($s_e_issn,0,4).'-'.substr($s_e_issn,4,4);
        
        $qp->buildQuery(format_string('(!field0:(!value0) OR !field1:(!value1)) AND !field2:(!value2*)', array(
            '!field0' => islandora_solr_lesser_escape(variable_get('lib4ri_pub_db_journ_issn_solr_field')),
            '!value0' => islandora_solr_lesser_escape($s_issn),
            '!field1' => islandora_solr_lesser_escape(variable_get('lib4ri_pub_db_journ_eissn_solr_field')),
            '!value1' => islandora_solr_lesser_escape($s_e_issn),
            '!field2' => islandora_solr_lesser_escape('PID'),
            '!value2' => 'journals',
        )));
        
        
        
        $qp->solrParams['fl'] = implode(',', array('PID',variable_get('lib4ri_pub_db_journ_title_solr_field'), variable_get('lib4ri_pub_db_abbr_title_solr_field'), variable_get('lib4ri_pub_db_journ_publish_solr_field'), variable_get('lib4ri_pub_db_journ_issn_solr_field'), variable_get('lib4ri_pub_db_journ_eissn_solr_field')));
        $qp->solrParams['fq'] = array();
        $qp->executeQuery(FALSE, TRUE);

        $found = 0;
        foreach ($qp->islandoraSolrResult['response']['objects'] as $object) {
            $found = 1;
            $doc = $object['solr_doc'];
            $title_node->nodeValue = $doc[variable_get('lib4ri_pub_db_journ_title_solr_field')][0];
            $id->nodeValue = $doc['PID'];
            $abbrev_title->nodeValue = $doc[variable_get('lib4ri_pub_db_abbr_title_solr_field')][0];
            $publisher->nodeValue = $doc[variable_get('lib4ri_pub_db_journ_publish_solr_field')][0];
            $issn->nodeValue = $doc[variable_get('lib4ri_pub_db_journ_issn_solr_field')][0];
            $e_issn->nodeValue = $doc[variable_get('lib4ri_pub_db_journ_eissn_solr_field')][0];             
        }
        
        if (!$found){
            $title_node->nodeValue = $title.' (NOT FOUND)';
            $this->setMessage('Journal not found in DORA', 'warning');
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

class ThreeRiMetaDataEnricher extends Lib4riMetaDataEnricher{
    
}

class PsiMetaDataEnricher extends Lib4riMetaDataEnricher{
    
    public function enrich(){
        $this->addStdName();
        $this->checkJournal();
        $this->addBeamlines();
    }
    
    public function addBeamlines(){
        if (module_exists('protein_db')){
            $this->xpath = new DOMXPath($this->dom);
            module_load_include('inc', 'protein_db', 'includes/define');
            
            $res = db_select(PROTEIN_DB_DATA_TABLE,'f')
            ->fields('f', array('pmid', 'facility', 'beamline'))
            ->condition('doi', $this->ids['doi'], '=')
            ->execute();
            
            $bls = [];
            foreach ($res as $bl) {
                array_push($bls, $bl);
            }
            
            $extension = $this->xpath->query("//mods:mods/mods:extension")[0];
            if (is_null($extension)){
                $extension = $this->dom->createElement('extension');
                $this->dom->documentElement->appendChild($extension);
            }
            
            $rfs = $this->xpath->query("//mods:mods/mods:extension/mods:researchFacilities")[0];
            if (is_null($rfs)){
                $rfs = $this->dom->createElement('researchFacilities');
                $extension->appendchild($rfs);
            }
            
            foreach ($bls as $bl){
                $rf = $this->dom->createElement('researchFacility');
                $fac = $this->dom->createElement('facility', $bl->facility);
                $beam = $this->dom->createElement('beamline', $bl->beamline);
                
                $rf->appendchild($fac);
                $rf->appendchild($beam);
                
                $rfs->appendchild($rf);
            }
            
            $pmid = $this->xpath->query("//mods:mods/mods:identifiar [@type=\"pmid\"]")[0];
            if (is_null($rfs)){
                $pmid = $this->dom->createElement('identifier', $bls[0]->pmid);
                $pmid->setAttribute('type','pmid');
                $this->dom->documentElement->appendChild($pmid);
            }
            
        }
        return $this;
    }
 
    public function addStdName(){
        module_load_include('inc', 'lib4ri_pub_db', 'includes/functions');
        
        $this->xpath = new DOMXPath($this->dom);
        $sections = $this->xpath->query(variable_get('lib4ri_pub_db_auth_xpath_query'));
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
                    $this->setMessage('Multiple matches for auhor '.$g_name.' '.$f_name, 'warning');
                }
                if (sizeof($auth_data) == 0){
                    $auth_data[0]['std_name'] = '4RI author. No matches.';
                    $auth_data[0]['pid'] = '';
                    $affil_search = 0;
                    $this->setMessage('No matches for auhor '.$g_name.' '.$f_name, 'warning');
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
                    $unit_data = get_authors_unit_from_aff_name($auth_data[0]['group'])[0];
                    $unit_id = $unit_data['g_pid'];
                    $unit_name = $unit_data['g_cname'];
                    $affil_data = get_authors_affiliation_from_aff_name($unit_name);
                    
                    $elem_uid = $this->dom->createElement('nameIdentifier',$unit_id);
                    $elem_uid->setAttribute('type','organizational unit id');
                    $section->appendChild($elem_uid);
                    
                    $elem_group = $this->dom->createElement('affiliation',$unit_name);
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
    
}

/*******************************************************************************************
*    Classes to validate IDs                                                               *                                                              
*******************************************************************************************/

class IdValidator{
    protected $mods;
    protected $messages = [];
    protected $id;
    protected $idsolrfield;
    protected $serv;
    protected $pub_type_checker;
    
    
    public function __construct() {
        $this->setSolrfield();
    }
    
    public function setId($id){
        $this->id = $id;
        return $this;
    }

//     protected function setServant($serv){
//         $this->serv = $serv;
//     }
    
    public function validate(){
        $same_id_obj = $this->getSameIdObjects();
        if ($same_id_obj == TRUE){
            $this->mods = FALSE;
        }
        else{
            $this->retrieveMods();
        }
        
        return $this;
    }
    
    protected function setSolrfield($solr_field){
        $this->idsolrfield = $solr_field;
        return $this;
    }
    
    protected function setServantId(){
        return $this;
    }
    
    protected function retrieveMods(){

    }
    
    
    protected function getSameIdObjects(){
        module_load_include('inc', 'islandora_solr', 'includes/utilities');
        module_load_include('inc', 'islandora', 'includes/utilities');

        $collectionsolrfield = variable_get('islandora_solr_member_of_collection_field', 'RELS_EXT_isMemberOfCollection_uri_ms');
        
        $query = $this->idsolrfield . ":\"" . islandora_solr_lesser_escape(trim($this->id)) . "\"";
        
        global $user;
        $original_user = $user;
        $old_state = drupal_save_session();
        drupal_save_session(FALSE);
        $user = user_load(1);
        
        $qp = new IslandoraSolrQueryProcessor();
        $qp->buildQuery($query);
        $qp->solrParams['fl'] = "PID, $this->idsolrfield, $collectionsolrfield";
        $qp->solrParams['sort'] = "PID asc";
        $qp->executeQuery(FALSE);
        
        $user = $original_user;
        drupal_save_session($old_state);
        
        $result = array();
        $result['objects'] = array();
        //    $result['collections'] = array();
        $result['count'] = 0;
        if (!empty($qp->islandoraSolrResult) && !empty($qp->islandoraSolrResult['response']) && isset($qp->islandoraSolrResult['response']['numFound']) && $qp->islandoraSolrResult['response']['numFound'] > 0){
            foreach ($qp->islandoraSolrResult['response']['objects'] as $curobj) {
                $pid = $curobj['PID'];
                $result['objects'][$pid] = array('pid' => $pid,
                    'doi' => $curobj['solr_doc'][$doisolrfield],
                    'collections' => ($curobj['solr_doc'][$collectionsolrfield] ? $curobj['solr_doc'][$collectionsolrfield] : array('')),
                );
                $result['count']++;
            }
        }
        
        if ($result['count'] == 0) {
            return FALSE;
        }
        else{
            global $base_url;
            $collections = array_map(function($val){return 'info:fedora/'.$val;},array_map('trim',explode(',',variable_get('lib4ri_pub_db_search_collections'))));
            $in_collection = "";
            foreach ($result['objects'] as $object){
                if (sizeof(array_intersect($collections, $object['collections'])) > 0){
                    $in_collection .= ' <a href="'.$base_url.'/islandora/object/'.$object['pid'].'">'.$object['pid'].'</a>';
                    foreach ($object['collections'] as $collection){
                        $in_collection .= ' ('.explode('/', $collection)[1].')';
                    }
//                    return TRUE;
                    //break;
                }
            }
            $this->setMessage('Object(s) with same ID already present in DORA: '.$in_collection, 'error');
            return TRUE;
        }
        
        
        
    }
    
    protected function setMessage($message, $type = 'status'){
        array_push($this->messages, array('message' => $message, 'type' => $type));
    }
    
    protected function fetchFromScopus(){
        if (variable_get('lib4ri_pub_db_scopus_use')){
            $data_retrieveng_class = variable_get('lib4ri_pub_db_scopus_data_class');
            $this->serv = new $data_retrieveng_class();
            $this->pub_type_checker = new ScopusPubTypeMatcher();
//            $this->serv = new Scopus2ModsServant();
            $this->setServantId();
            $this->serv->setKey(variable_get('lib4ri_pub_db_scopus_api_key'))->serve();
            $this->mods = $this->serv->getProcessedDom()[0];
            
            if ($this->mods != FALSE){
                if (!$this->pub_type_checker->check($this->serv->getFetchedDom()[0])){
                    $this->setMessage('The publication does not appear to be a journal article', 'error');
                    $this->mods = FALSE;
                }
                else {
                    $this->setMessage('Data fetched from Scopus', 'status');
                }
            }
            else {
                $this->setMessage('Cannot fetch data from Scopus', 'warning');
            }
        }
        
        return $this;
    }

    protected function fetchFromXref(){
        if (variable_get('lib4ri_pub_db_xref_use')){
            $data_retrieveng_class = variable_get('lib4ri_pub_db_xref_data_class');
            $this->serv = new $data_retrieveng_class();
            $this->pub_type_checker = new CrossrefPubTypeMatcher();
//            $this->serv = new Crossref2ModsServant();
            $this->setServantId();
            $this->serv->setPid(variable_get('lib4ri_pub_db_xref_pid'))->serve();
            $this->mods = $this->serv->getProcessedDom()[0];
        
            if ($this->mods != FALSE){
                $this->setMessage('Data fetched from Crossref', 'status');
                if (!$this->pub_type_checker->check($this->serv->getFetchedDom()[0])){
                    $this->setMessage('The publication does not appear to be a journal article', 'error');
                }
            }
            else {
                $this->setMessage('Cannot fetch data from Crossref', 'warning');
            }
        }
        
        return $this;
    }
    
    public function getMessages(){
        return $this->messages;
    }
    
    public function getMods(){
        return $this->mods;
    }
    
}

class DoiValidator extends IdValidator{
    
    protected function setSolrfield(){
        $this->idsolrfield = variable_get('lib4ridora_solr_field_document_doi', 'mods_identifier_doi_mlt');
    }
    
    protected function setServantId(){
        $this->serv->setDoi($this->id);
        return $this;
    }
    
    protected function retrieveMods(){
        $this->fetchFromScopus();
        
        if ($this->mods == FALSE){
            $this->fetchFromXref();        
        }
        
        return $this;
    }
    
}

class EidValidator extends IdValidator{

    protected function setSolrfield(){
        $this->idsolrfield = 'mods_identifier_scopus_mlt';
    }
    
    protected function setServantId(){
        $this->serv->setEid($this->id);
        return $this;
    }
    
    protected function retrieveMods(){
        $this->fetchFromScopus();
     
        return $this;
    }
}

class ScopusPubTypeMatcher {
    public function __construct() {
        
    }

    public function check($dom){
        $type = $dom->getElementsByTagName("abstracts-retrieval-response")->item(0)->getElementsByTagName("coredata")->item(0)->getElementsByTagName("aggregationType")->item(0)->nodeValue;
        $subtype = $dom->getElementsByTagName("abstracts-retrieval-response")->item(0)->getElementsByTagName("coredata")->item(0)->getElementsByTagName("subtypeDescription")->item(0)->nodeValue;
        if ($type == 'Journal' AND ($subtype == 'Article' OR $subtype == 'Review' OR $subtype == 'Conference Paper' OR $subtype == 'Letter' OR $subtype == 'Note' OR $subtype == 'Editorial')){
            return TRUE;
        }
        return FALSE;   
    }
}

class CrossrefPubTypeMatcher {
    public function __construct() {
        
    }
    
}