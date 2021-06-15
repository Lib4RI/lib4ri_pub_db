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
				<identifier type="isbn"><xsl:value-of select="/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn[@media_type='electronic']"/></identifier>
			</xsl:when>
			<xsl:otherwise>
				<xsl:choose>
					<xsl:when test="/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn">
						<identifier type="isbn"><xsl:value-of select="/doi_records/doi_record/crossref/conference/proceedings_metadata/isbn"/></identifier>
					</xsl:when>
				</xsl:choose>								
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
			<titleInfo>
				<title>
					<xsl:choose>
						<xsl:when test="/doi_records/doi_record/crossref/conference/proceedings_metadata/proceedings_title != /doi_records/doi_record/crossref/conference/event_metadata/conference_name">
								<xsl:value-of select="/doi_records/doi_record/crossref/conference/proceedings_metadata/proceedings_title"/>
						</xsl:when>
					</xsl:choose>
				</title>
			</titleInfo>	
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
						<start><xsl:value-of select="/doi_records/doi_record/crossref/conference/conference_paper/pages/first_page"/></start>
						<end><xsl:value-of select="/doi_records/doi_record/crossref/conference/conference_paper/pages/last_page"/></end>
				</extent>
			</part>
			<originInfo>
				<publisher><xsl:value-of select="/doi_records/doi_record/crossref/conference/proceedings_metadata/publisher/publisher_name"/></publisher>
			</originInfo>			
		</relatedItem>
		<name type="conference"><xsl:value-of select="/doi_records/doi_record/crossref/conference/event_metadata/conference_name"/></name>
		<originInfo>
			<place>
				<placeTerm type="text"><xsl:value-of select="/doi_records/doi_record/crossref/conference/event_metadata/conference_location"/></placeTerm>
			</place>
		</originInfo>
		<originInfo>
			<dateOther type="conferenceDate">
				<xsl:value-of select="/doi_records/doi_record/crossref/conference/event_metadata/conference_date/@start_year"/>.
<xsl:value-of select="/doi_records/doi_record/crossref/conference/event_metadata/conference_date/@start_month"/>.
<xsl:value-of select="/doi_records/doi_record/crossref/conference/event_metadata/conference_date/@start_day"/>-
<xsl:value-of select="/doi_records/doi_record/crossref/conference/event_metadata/conference_date/@end_year"/>.
<xsl:value-of select="/doi_records/doi_record/crossref/conference/event_metadata/conference_date/@end_month"/>.
<xsl:value-of select="/doi_records/doi_record/crossref/conference/event_metadata/conference_date/@end_day"/>
			</dateOther>
		</originInfo>				
		<originInfo>
			<dateIssued encoding="w3cdtf" keyDate="yes"><xsl:value-of select="/doi_records/doi_record/crossref/conference/proceedings_metadata/publication_date/year"/></dateIssued>
		</originInfo>
		<note type="quality_control_ID">cro</note>
		</mods>
	</xsl:template>
</xsl:stylesheet>
