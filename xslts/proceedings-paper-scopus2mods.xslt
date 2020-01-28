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
	<xsl:template match="/">
	<mods>
		<titleInfo>
			<title><xsl:value-of select="/dtd:abstracts-retrieval-response/item/bibrecord/head/citation-title/titletext"/></title>
		</titleInfo>
		<identifier type="doi"><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:doi"/></identifier>
  		<identifier type="scopus"><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/dtd:eid"/></identifier>
  		<identifier type="pmid"><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/dtd:pubmed-id"/></identifier>
  		<language>
			<languageTerm type="code" authority="iso639-3"><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:language/@xml:lang"/></languageTerm>
		</language>		
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
		  				<xsl:when test="@fourri='true'">
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
		  				<xsl:when test="@fourri='true'">
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
		<originInfo>
			<place>
				<placeTerm type="text"><xsl:value-of select="/dtd:abstracts-retrieval-response/item/bibrecord/head/source/additional-srcinfo/conferenceinfo/confevent/conflocation/city"/></placeTerm>
			</place>
		</originInfo>
		<originInfo>
			<dateOther type="conferenceDate"></dateOther>
		</originInfo>
		<relatedItem type="host">
			<titleInfo>
				<title>
					<xsl:value-of select="/dtd:abstracts-retrieval-response/item/bibrecord/head/source/issuetitle"/>
				</title>
			</titleInfo>	
			<xsl:for-each select="/dtd:abstracts-retrieval-response/item/bibrecord/head/source/contributor-group/contributor[@role='edit']">
				    <name type="personal">
  					<namePart type="family"><xsl:value-of select="ce:surname"/></namePart>
  					<namePart type="given"><xsl:value-of select="ce:given-name"/></namePart>
  					<role>
  						<roleTerm authority="marcrelator" type="text">editor</roleTerm>
  					</role>
  					</name>
			</xsl:for-each>
			<relatedItem type="series">
				<titleInfo>
					<title><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:publicationName"/></title>
				</titleInfo>
				<identifier type="issn"><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:issn"/></identifier>
			</relatedItem>
			<part>
				<detail type="volume">
					<number><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:volume"/></number>
				</detail>
				<detail type="issue">
					<number/>
				</detail>
				<extent unit="pages">
					<xsl:choose>
						<xsl:when test="/dtd:abstracts-retrieval-response/dtd:coredata/prism:startingPage">
							<start><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:startingPage"/></start>
							<end><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/prism:endingPage"/></end>
						</xsl:when>
						<xsl:otherwise>
							<start><xsl:value-of select="/dtd:abstracts-retrieval-response/dtd:coredata/dtd:article-number"/></start>
							<end></end>
						</xsl:otherwise>
					</xsl:choose>								
					<end/>
				</extent>
			</part>
		</relatedItem>
		<originInfo>
			<dateIssued encoding="w3cdtf" keyDate="yes"><xsl:value-of select="/dtd:abstracts-retrieval-response/item/bibrecord/head/source/publicationdate/year"/></dateIssued>
		</originInfo>
		<originInfo>
			<publisher><xsl:value-of select="/dtd:abstracts-retrieval-response/item/bibrecord/head/source/publisher/publishername"/></publisher>
			<place>
				<placeTerm type="text"></placeTerm>
			</place>
		</originInfo>
	</mods>
	</xsl:template>
</xsl:stylesheet>
