<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
  xmlns="http://www.loc.gov/mods/v3" 
  xmlns:mods="http://www.loc.gov/mods/v3" 
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
  xmlns:xlink="http://www.w3.org/1999/xlink"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
>

  <xsl:output method="xml" indent="yes"/>
	<xsl:template match="/">
		<mods>
		<titleInfo>
			<title><xsl:value-of select="/doi_records/doi_record/crossref/conference/conference_paper/titles/title"/></title>
		</titleInfo>
		<xsl:choose>
			<xsl:when test="/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn[@media_type='electronic']">
				<identifier type="isbn"><xsl:value-of select="substring(/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn[@media_type='electronic'],1,3)"/>-<xsl:value-of select="substring(/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn[@media_type='electronic'],4,1)"/>-<xsl:value-of select="substring(/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn[@media_type='electronic'],5,5)"/>-<xsl:value-of select="substring(/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn[@media_type='electronic'],10,3)"/>-<xsl:value-of select="substring(/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn[@media_type='electronic'],13,1)"/></identifier>
			</xsl:when>
			<xsl:otherwise>
				<identifier type="isbn"><xsl:value-of select="substring(/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn,1,3)"/>-<xsl:value-of select="substring(/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn,4,1)"/>-<xsl:value-of select="substring(/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn,5,5)"/>-<xsl:value-of select="substring(/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn,10,3)"/>-<xsl:value-of select="substring(/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn,13,1)"/></identifier>
			</xsl:otherwise>					
		</xsl:choose>		
		<identifier type="doi"><xsl:value-of select="/doi_records/doi_record/crossref/conference/conference_paper/doi_data/doi"/></identifier>
  		<xsl:for-each select="/doi_records/doi_record/crossref/conference/conference_paper/contributors/person_name[@contributor_role='author']">
  			<xsl:choose>
  				<xsl:when test="@sequence='first'">
  					<name type="personal" usage="primary">
  					<namePart type="family"><xsl:value-of select="surname"/></namePart>
  					<namePart type="given"><xsl:value-of select="given_name"/></namePart> <!--To be checked--> 
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
  					<namePart type="family"><xsl:value-of select="surname"/></namePart>
  					<namePart type="given"><xsl:value-of select="given_name"/></namePart>
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
		<relatedItem type="host">
			<xsl:for-each select="/doi_records/doi_record/crossref/conference/conference_paper/contributors/person_name[@contributor_role='editor']">
		    	<name type="personal">
  		    		<namePart type="family"><xsl:value-of select="surname"/></namePart>
  		    		<namePart type="given"><xsl:value-of select="given_name"/></namePart>
		  			<role>
  						<roleTerm authority="marcrelator" type="text">editor</roleTerm>
  					</role>
  				</name>
			</xsl:for-each>
			<part>
				<extent unit="pages">
						<start><xsl:value-of select="/doi_records/doi_record/crossref/conference/conference_paper/first_page"/></start>
				</extent>
			</part>
		</relatedItem>
		</mods>
	</xsl:template>
</xsl:stylesheet>
