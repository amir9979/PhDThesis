
function ConfigurationView(data, elementID, configuration, events){
	var self = this;
	this.render = function(){
		$('#'+elementID).html("");
		self.renderDefualtVis();
		self.renderAnimationTime();
		self.renderGradiante();
		self.renderChosenScript();
	}

	this.renderDefualtVis = function(){
		$('#'+elementID).append('<p><label for="defaultVis">Select the defaut visualization:</label></p><select name="defaultVis" id="defaultVis"></select>');
		$.each(visualizations, function(index, visualization) {
			$("#defaultVis").append('<option id="defaultVis_'+index+'" value="'+index+'">'+visualization.displayName+'</option>');
		});
		$('#defaultVis_'+configuration.currentConfig.defaultView).attr("selected","selected");
		$("#defaultVis").selectmenu({
			change: function( event, data ) {
				configuration.currentConfig.defaultView = data.item.value;
				configuration.saveConfig();
			}
		});
	}

	this.renderAnimationTime = function(){
		$('#'+elementID).append('<p><label for="anitime">Animation time (ms):</label><input type="text" id="anitime" readonly style="border:0; color:#f6931f; font-weight:bold;"></p><div id="slider-range-min"></div>');

		$( "#slider-range-min" ).slider({
			range: "min",
			value: 700,
			min: 0,
			max: 5000,
			slide: function( event, ui ) {
				$( "#anitime" ).val( ui.value );
				configuration.currentConfig.animationTransitionTime = ui.value;
				configuration.saveConfig();
			}
		});
		$( "#anitime" ).val( $( "#slider-range-min" ).slider( "value" ) );
	}

	this.renderGradiante = function(){
		$('#'+elementID).append('<div><label>Gradiante:</label><div><div id="color-box0" class="color-box"></div><div id="color-box1" class="color-box"></div><div id="color-box2" class="color-box"></div></div></div>');

		$.each(configuration.currentConfig.normalGradiante,function(index,value){
			$('#color-box'+index).colpick({
				layout:'hex',
				color:$.colpick.rgbToHex(value),
				onSubmit:function(hsb,hex,rgb,el) {
					$(el).css('background-color', '#'+hex);
					$(el).colpickHide();
					configuration.currentConfig.normalGradiante[index] = rgb;
					configuration.saveGradiante();
				}
			})
			.css('background-color', '#'+$.colpick.rgbToHex(value));
		});
	}

	this.renderChosenScript = function(){
		$('#'+elementID).append('<br /><br/><div class="ui-widget"><label for="tags">Additional scripts to load: </label><br /><input id="tags" size="50"></div>');

		function split( val ) {
			return val.split( /,\s*/ );
		}
		function extractLast( term ) {
			return split( term ).pop();
		}
		$( "#tags" )
// don't navigate away from the field on tab when selecting an item
.bind( "keydown", function( event ) {
	if ( event.keyCode === $.ui.keyCode.TAB &&
		$( this ).autocomplete( "instance" ).menu.active ) {
		event.preventDefault();
}
})
.autocomplete({
	minLength: 0,
	source: function( request, response ) {
// delegate back to autocomplete, but extract the last term
response( $.ui.autocomplete.filter(
	configuration.currentConfig.scriptsLoadAutoComplete, extractLast( request.term ) ) );
},
create: function() {
	var finalTerm = [];
	$.each(configuration.currentConfig.scriptsLoad, function(index, term) {
		if(term.length > 3 && !(finalTerm.indexOf(term) >= 0) && urlExists(term.trim())){
			finalTerm.push(term.trim());
		}
	});
	configuration.currentConfig.scriptsLoad = finalTerm;
	configuration.saveConfig();
    this.value = configuration.currentConfig.scriptsLoad.join( ", " );
},
focus: function() {
// prevent value inserted on focus
return false;
},
change: function( event, ui ) {
	var terms = split( this.value );
	var finalTerm = [];
	$.each(terms, function(index, term) {
		if(term.length > 3 && !(finalTerm.indexOf(term) >= 0) && urlExists(term.trim())){
			finalTerm.push(term.trim());
		}
	});
	finalTerm = jQuery.unique( finalTerm );
	configuration.currentConfig.scriptsLoad = finalTerm;
	configuration.currentConfig.scriptsLoadAutoComplete = configuration.currentConfig.scriptsLoadAutoComplete.concat(finalTerm).unique();
	configuration.saveConfig();
},
select: function( event, ui ) {
	var terms = split( this.value );
// remove the current input
terms.pop();
// add the selected item
terms.push( ui.item.value );
// add placeholder to get the comma-and-space at the end
terms.push( "" );
this.value = terms.join( ", " );
return false;
}
});
}
}


Array.prototype.unique = function()
{
    var tmp = {}, out = [];
    for(var i = 0, n = this.length; i < n; ++i)
    {
        if(!tmp[this[i]]) { tmp[this[i]] = true; out.push(this[i]); }
    }
    return out;
}

function urlExists(testUrl) {
 var http = jQuery.ajax({
    type:"HEAD",
    url: testUrl,
    async: false
  })
  return http.status == 200;
}