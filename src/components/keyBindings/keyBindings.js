function keyBindings(configuration,zoomEvents){
	console.log(configuration.currentConfig);
	var keyBindingsD = configuration.currentConfig.keyBindings;

	function getKeyBindingByName(name){
		for (var i = keyBindingsD.length - 1; i >= 0; i--) {
			if(keyBindingsD[i].name == name){
				return keyBindingsD[i];
			}
		};
		return null;
	}

	function getKeyBindingByKeyCodes(keyCodes){
		for (var i = keyBindingsD.length - 1; i >= 0; i--) {
			if(arrayEquals(keyCodes,keyBindingsD[i].keyCodes)){
				return keyBindingsD[i];
			}
		};
		return null;
	}

	function setKeyBinding(name,func){
		getKeyBindingByName(name).func = func;
	}


	setKeyBinding("Zoom Reset",zoomEvents.zoomReset);
	setKeyBinding("Zoom In",zoomEvents.zoomIn);
	setKeyBinding("Move Left",zoomEvents.left);
	setKeyBinding("Move Up",zoomEvents.up);
	setKeyBinding("Zoom Out",zoomEvents.zoomOut);
	setKeyBinding("Move Right",zoomEvents.right);
	setKeyBinding("Move Down",zoomEvents.down);
	console.log(configuration.currentConfig);

	var pressedKeys = [];
	var timeOut;
	document.onkeydown = function(e) {
		clearTimeout(timeOut);
		pressedKeys.push(e.keyCode);
		keyBinding = getKeyBindingByKeyCodes(pressedKeys);
		if(keyBinding != null){
			keyBinding.func();
			pressedKeys = [];
		}
		else{
			timeOut = setTimeout(function(){
				pressedKeys = [];
			}, 1500);
		}
	}

}

function arrayEquals(array1,array2){
	if(array1.length != array2.length)
		return false;
	for (var i = array1.length - 1; i >= 0; i--) {
		if(array1[i] != array2[i]){
			return false;
		}
	};
	return true;
}