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
				</extent>
			</part>
  		</relatedItem>
  		<note type="quality_control_ID">sco</note>
  		<note type="quality_control">Yes</note>
  		<extension>
  			<fundingReferences>
  				<xsl:for-each select="/dtd:abstracts-retrieval-response/item/xocs:meta/xocs:funding-list/xocs:funding">
  					<xsl:choose> 
  						<xsl:when test="xocs:funding-agency-id[.='http://data.elsevier.com/vocabulary/SciValFunders/100010661'] or xocs:funding-agency-id[.='http://data.elsevier.com/vocabulary/SciValFunders/501100007601']">
  							<xsl:for-each select="xocs:funding-id">
	  							<fundingReference>
									<funderName>European Commission</funderName>
									<funderIdentifier funderIdentifierType="Crossref_Funder">http://dx.doi.org/10.13039/501100000780</funderIdentifier>
									<fundingStream>Horizon 2020 Framework Programme</fundingStream>
									<awardTitle></awardTitle>
									<awardNumber><xsl:value-of select="current()"/></awardNumber>
								</fundingReference>
							</xsl:for-each>
  						</xsl:when>

  						<xsl:when test="xocs:funding-agency-id[.='http://data.elsevier.com/vocabulary/SciValFunders/100011102'] or xocs:funding-agency-id[.='http://data.elsevier.com/vocabulary/SciValFunders/501100004963']">
  							<xsl:for-each select="xocs:funding-id">
	  							<fundingReference>
									<funderName>European Commission</funderName>
									<funderIdentifier funderIdentifierType="Crossref_Funder">http://dx.doi.org/10.13039/501100000780</funderIdentifier>
									<fundingStream>Seventh Framework Programme</fundingStream>
									<awardTitle></awardTitle>
									<awardNumber><xsl:value-of select="current()"/></awardNumber>
									</fundingReference>
							</xsl:for-each>									
  						</xsl:when>

  						<xsl:when test="xocs:funding-agency-id[.='http://data.elsevier.com/vocabulary/SciValFunders/501100001711']">
  							<xsl:for-each select="xocs:funding-id">
	  							<fundingReference>
									<funderName>Swiss National Science Foundation</funderName>
									<funderIdentifier funderIdentifierType="Crossref_Funder">http://dx.doi.org/10.13039/501100001711</funderIdentifier>
									<fundingStream>SNSF</fundingStream>
									<awardTitle></awardTitle>
									<awardNumber><xsl:value-of select="current()"/></awardNumber>
								</fundingReference>
							</xsl:for-each>				
  						</xsl:when>	
  					</xsl:choose>
  				</xsl:for-each>
  			</fundingReferences>
  		</extension>
	</mods>
	</xsl:template>
</xsl:stylesheet>
