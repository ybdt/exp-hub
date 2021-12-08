function getCookie(c_name) {
  if (document.cookie.length>0) {
    c_start=document.cookie.indexOf(c_name + "=");
    if (c_start!=-1) {
      c_start=c_start + c_name.length+1;
      c_end=document.cookie.indexOf(";",c_start);
      if (c_end==-1) {c_end=document.cookie.length;}
        return unescape(document.cookie.substring(c_start,c_end));
    }
  }
  return "";
}

if (typeof URLobj == 'undefined') {var URLobj = {};}

URLobj.init = function(pathname) {	

	fp=document.location.pathname.split('/');
	pn=fp.pop();
	if (pn != "" && pn.split('.').length <=1) {pathname=document.location.pathname+'/';}	
		
    this.pathname=(pathname)?pathname:document.location.pathname;
    /* logged in or out? */
    this.lcookie=getCookie("OAMAuthnCookie");
    this.prop7=(this.lcookie && this.lcookie!="loggedout" && !this.lcookie.match(/loggedout/))?"Logged In":"Logged Out"; 
	/*hightoucheval page*/ 
	if(/assessment/.test(this.pathname)) {
	   if (typeof(jQuery("input[name='publicPage']").attr('value')) != 'undefined'){
		   this.prop7=(jQuery("input[name='publicPage']").attr('value'))?'Logged Out' : 'Logged In'
	   }
	}
		
    this.prop15="";
    /* international */
  	this.pcookie=getCookie("pszGeoPref");
    if (this.pcookie && this.pcookie!="") {
        if (this.pcookie.match(/^\w+$/)) {
            this.prop26=this.pcookie;
        }
    } 
	this.country=["de","fr","cn","jp","es","latam","ru","tw","at","br","it","kr","ap","cz","nl","pl","ch","se","be","caen","cafr","uk","au","in","nz","hu","mena","eu","il","tr","mx","co","ar","pe","cl","ve","sa","ae","za","cr","pt","sg","id","my","dk","no","fi"];	 
    this.siteid=["vmwde","vmwfr","vmwcn","vmwjp","vmwes","vmwlasp","vmwru","vmwtw","vmwat","vmwbr","vmwit","vmwkr","vmwap","vmwcz","vmwnl","vmwpl","vmwch","vmwse","vmwbeen","vmwcaen","vmwcafr","vmwuk","vmwau","vmwin","vmwnz","vmwhu","vmwmena","vmweu","vmwil","vmwtr","vmwmx","vmwco","vmwar","vmwpe","vmwcl","vmwve","vmwsa","vmwae","vmwza","vmwcr","vmwpt","vmwsg","vmwid","vmwmy","vmwdk","vmwno","vmwfi"];
	
    this.ccode="vmware";
    this.ccodeidx="undef";

   	var domain_src = new Array("mylearn1");  /*source sites that need be combined*/
	var domain_target = new Array("mylearn"); /*target sites*/
	
	var icase = new Array("mylearn");  /*all sites that their url are not case sensitive*/	
	var str_domain = document.location.host;	
	var len = domain_src.length;
	var ilen = icase.length;
	for (var i=0; i<len; i++) {
		if (str_domain.toLowerCase().indexOf(domain_src[i]) >= 0) {
			str_domain = str_domain.replace(domain_src[i],domain_target[i]);			
			break;  
		}
	}
	for (var i=0; i<ilen; i++) {
		if (str_domain.toLowerCase().indexOf(icase[i]) >=0) {
			this.pathname = this.pathname.toLowerCase();
			break;
		}
	}

    this.host = new Array();
    this.host = str_domain.split('.');
    if (this.host.length > 2) {
        if (this.host[1] != "vmware"){
            this.subdomain=(this.host[0] != "www" && this.host[0] != "") ? this.host[1]+","+this.host[0] : this.host[1];
        }else {this.subdomain=this.host[0] || "www";}
    } else if (this.host[0] != "vmware") {this.subdomain=this.host[0];}
    else {this.subdomain="www";}

    /* path & pagename */
    this.pagename="";
    this.path = new Array();
    this.path = this.pathname.split('/');
    this.path.shift();
	if (this.path.length>2 && this.path[this.path.length-2] != 'evalcenter') {
    	this.file = this.path.pop();
	} else {
		this.file = this.path.pop() || "index.html"; }
	this.file = this.file.replace(/;?jsessionid.+$/i,"");
   
    /* check for international site */
	/* for CA/FR and CA/EN */
	var countrydir = this.path[0];
	if (countrydir == "ca") { countrydir += this.path[1]; }  
	for (var c=0; c<this.country.length; c++) {
        if (this.country[c]==countrydir) {
	    this.ccode=this.siteid[c];
	    this.ccodeidx=c;
	}
    }
    this.hier1=this.ccode+",";
    /* check for subdomain */
    if (this.subdomain && this.subdomain!="www"){this.hier1+=this.subdomain+",";}
    /* set s.heir1 */ 
    if (this.path.length > 0) {
	for (var i=0; i<this.path.length; i++) {
	    if (i==0) {
		if (this.ccodeidx!="undef" && this.country[this.ccodeidx]==this.path[i]) {continue;}
		if (this.subdomain && this.subdomain==this.path[i]) {continue;}
	    }
	    this.hier1+=(this.path[i]+",");
    }
    } 
    this.hier1=this.hier1.replace(/,$/,"");
    /* parse query string */
    if (document.location.search) {	
		var qs = {};
		document.location.search.replace(
			new RegExp("([^?=&]+)(=([^&]*))?", "g"),
			function($0, $1, $2, $3) { qs[$1] = $3; }
		);
		this.id=qs['id'];
		this.p=qs['p'];
		this.externalId=qs['externalId'];
		this.q=qs['q'];
		this.file=qs['file']? this.file +' : '+qs['file'] : this.file;
		this.k=qs['k'];
 		this.lang=qs['lang'];
 		this.plainview = qs['plainview'];
	}
	
   /* customer videos */
   if (this.pathname.match("success_video.html")) {
   	this.hier1+=",success_video";
   	this.file=this.id;
   }   
   /* investor relations */
    if (this.pathname.match("/phoenix.zhtml")) {
	if (this.p) this.hier1+=','+this.p;
	if (this.id) this.file=this.id;
    }
   /* knowledge base */
    if (this.subdomain=="kb") {
        this.hier1=this.hier1.replace(/,microsites/,"");
        if (this.externalId) {        	
	    	if(this.plainview){
                this.hier1 += ("," + this.file);
            } 
	    	this.file=this.externalId;
	} /*else if (this.pathname.match("/selfservice/(microsites/)?search(Entry)?.do") || (this.pathname.match("/selfsupport/s3portal.portal") && this._pageLabel=="s3Portal_page_knova_search")) {
            if (document.forms[0].id.match(/searchForm/)) {
                this.prop6=document.forms[0].searchString.value;
                this.prop15="Knova_Search";
             } else if(frames[0].document && frames[0].document.forms[0].searchString.value != "") {
                 this.prop6=frames[0].document.forms[0].searchString.value;
                 this.prop15="Knova_Search";
             }
        }*/
    }
	/* add GSS search terms */
	if (this.subdomain =="gss") {
		this.prop6=document.forms[0].txtSearch.value;
		if (!this.prop6) {this.prop6=(this.k)?this.k.toLowerCase():'';}
		this.prop15="GSS_Search";
	}	
   /* technical papers */
    if (this.pathname.match("/techresources/(cat/)?[0-9]+")) 
	this.file=document.title;
  /*webcast emea page */
   if (/webcasts\.vmware\.com\/clients\/vmware\/emea\/index.html/.test(document.URL) && typeof(this.lang) != 'undefined') {       
   	 this.file= this.lang;
    }	
				
};

var url = new URLobj.init();

var campaign_cookie = getCookie('s_campaign');
  
     url.hierarchy = new Array();			
     url.hierarchy = url.hier1.split(",");
     for (var i = 0; i < url.hierarchy.length; i++) {
        if (i <= 4) 
           eval("url.prop" + (i + 1) + "='" + url.hierarchy[i] + "';");
        }      
        for (var i = url.hierarchy.length; i < 5; i++) 
            eval("url.prop" + (i + 1) + "='" + url.hierarchy[url.hierarchy.length - 1] + "';");
        
        url.pagename = url.hier1.replace(/,/g, " : ");
		url.file=url.file.split('.')[0];
		if(url.file =="index" ){
			url.fullpagename = url.pagename;		
		}else 
			
		if (url.file !='') {
			url.fullpagename = url.pagename + " : " + url.file;
		} else { url.fullpagename = url.pagename; }

if(window.location.href.indexOf("/vmware/evalcenter") == -1) {
  window.utag_data = window.utag_data || {};
  utag_data.page_name = url.fullpagename;
  utag_data.site_section1 = url.prop1;
  utag_data.site_section2 = url.prop2;
  utag_data.site_section3 = url.prop3;
  utag_data.site_section4 = url.prop4;
  utag_data.site_section5 = url.prop5;
  utag_data.is_logged_in = url.prop7;
  utag_data.hier = url.hier1;
}

//utag_data.content_system = "Teamsite";
//utag_data.ip = dbInfo.ip || ''; 
