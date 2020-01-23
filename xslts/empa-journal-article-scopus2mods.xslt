<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
  xmlns="http://www.loc.gov/mods/v3" 
  xmlns:mods="http://www.loc.gov/mods/v3" 
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
  xmlns:xlink="http://www.w3.org/1999/xlink"
  xmlns:dtd="http://www.elsevier.com/xml/svapi/abstract/dtd"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:dn="http://www.elsevier.com/xml/svapi/abstract/dtd" 
  xmlns:ait="http://www.elsevier.com/xml/ani/ait" 
  xmlns:ce="http://www.elsevier.com/xml/ani/common" 
  xmlns:cto="http://www.elsevier.com/xml/cto/dtd" 
  xmlns:dc="http://purl.org/dc/elements/1.1/" 
  xmlns:prism="http://prismstandard.org/namespaces/basic/2.0/" 
  xmlns:xocs="http://www.elsevier.com/xml/xocs/dtd" 
  exclude-result-prefixes="dtd xsl prism dn ait ce cto dc prism xocs">
  
  <xsl:output method="xml" indent="yes"/>
  <xsl:variable name="internal_affiliation" select="/dtd:abstracts-retrieval-response/dtd:affiliation[dtd:affilname='Empa - Swiss Federal Laboratories for Materials Science and Technology']/@id" />
  <aff_id><xsl:value-of select="$internal_affiliation" /></aff_id>
	<xsl:template match="/">
	<mods>
		<titleInfo>
			<title><xsl:value-of select="/dtd:abstracts-retrieval-response/item/bibrecord/head/citation-title/titletext"/></title>
		</titleInfo>
		<originInfo>
    		<dateIssued encoding="w3cdtf" keyDate="yes"><xsl:value-of select="/dtd:abstracts-retrieval-response/item/ait:process-info/ait:date-sort/@year"/></dateIssued>
  		</originInfo>
  		<identifier type="doi"><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:doi"/></identifier>
  		<identifier type="scopus"><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/dtd:eid"/></identifier>
  		<identifier type="pmid"><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/dtd:pubmed-id"/></identifier>
  		<xsl:for-each select="/dtd:abstracts-retrieval-response/dtd:authors/dtd:author">
  			<xsl:choose>
  				<xsl:when test="@seq=1">
  					<name type="personal" usage="primary">
  					<namePart type="family"><xsl:value-of select="dtd:preferred-name/ce:surname"/></namePart>
  					<namePart type="given"><xsl:value-of select="dtd:preferred-name/ce:given-name"/></namePart> <!--To be checked--> 
  					<role>
  						<roleTerm authority="marcrelator" type="text">author</roleTerm>
  					</role>
  					<xsl:choose>
		  				<xsl:when test="dtd:affiliation/@id=$internal_affiliation">
		  					<fourri>true</fourri>
		  				</xsl:when>
		  			</xsl:choose>  					
  					</name>
  				 </xsl:when>
  				 <xsl:otherwise>
    				<name type="personal">
  					<namePart type="family"><xsl:value-of select="dtd:preferred-name/ce:surname"/></namePart>
  					<namePart type="given"><xsl:value-of select="dtd:preferred-name/ce:given-name"/></namePart>
  					<role>
  						<roleTerm authority="marcrelator" type="text">author</roleTerm>
  					</role>
		  			<xsl:choose>
		  				<xsl:when test="dtd:affiliation/@id=$internal_affiliation">
		  					<fourri>true</fourri>
		  				</xsl:when>
		  			</xsl:choose>  					
  					</name>    				
  				 </xsl:otherwise>
  			</xsl:choose>
		</xsl:for-each>  
		<subject>
		<topic/>
			<xsl:for-each select="/dtd:abstracts-retrieval-response/dtd:authkeywords/dtd:author-keyword">
				<topic><xsl:value-of select="current()"/></topic>
			</xsl:for-each>
		</subject>
  		<abstract><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/dc:description/abstract/ce:para"/></abstract>
  		<relatedItem type="host">
  			<titleInfo>
  				<title><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:publicationName"/></title>
  			</titleInfo>
  			<titleInfo type="abbreviated">
  				<title><xsl:value-of select="/dtd:abstracts-retrieval-response/item/bibrecord/head/source/sourcetitle-abbrev"/></title>
  				</titleInfo>
  			<originInfo>
  				<publisher><xsl:value-of select="/dtd:abstracts-retrieval-response/item/bibrecord/head/source/publisher/publishername"/></publisher>
  			</originInfo>
			<identifier type="journal id"></identifier>
			<identifier type="issn"><xsl:value-of select="/dtd:abstracts-retrieval-response/item/bibrecord/head/source/issn[@type='print']"/></identifier>
			<identifier type="e-issn"><xsl:value-of select="/dtd:abstracts-retrieval-response/item/bibrecord/head/source/issn[@type='electronic']"/></identifier>
			<part>
				<detail type="volume">
					<number><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:volume"/></number>
				</detail>
				<detail type="issue">
					<number><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:issueIdentifier"/></number>
				</detail>
				<extent unit="page">
					<start><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:startingPage"/></start>
					<end><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:endingPage"/></end>
				</extent>
			</part>
  		</relatedItem>
	</mods>
	</xsl:template>
</xsl:stylesheet>
