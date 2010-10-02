/**************************************************************************************
 *
 * CEGUI Imageset Exporter 1.0 - by Philipe - http://www.philipe.tym.sk
 *
 *************************************************************************************/

var scriptName = "CEGUI Imageset Exporter by Philipe";

// Save the current preferences
var startTypeUnits = app.preferences.typeUnits;
app.preferences.typeUnits = TypeUnits.PIXELS

// ok and cancel button
var okButtonID = 1;
var cancelButtonID = 2;

//default values
var imageName = "";
var imageFile = "";
var nativeHorzRes="1024";
var nativeVertRes = "768";
var autoScaled = "true";

// call function main 
main();
// Reset the application preferences
app.preferences.typeUnits = startTypeUnits;


function main(){

	// Do we have a document open?
	if (app.documents.length === 0) {
		alert("Please open some file", " Error", true);
		return;
	}
	
	if (showDialog() === cancelButtonID){
		return;
	}


	// Pop up save dialog
	var saveFile = File.saveDialog("Please select a file to export:", "Imageset file:*.imageset");

	// User Cancelled
	if(saveFile == null){
		return;
	}

	// set filePath and fileName to the one chosen in the dialog
	filePath = saveFile.path + "/" + saveFile.name;

	// create outfile
	var fileOut = new File(filePath);

	// clear dummyFile
	dummyFile = null;
	
	// Linefeed shizzle
	if ($.os.search(/windows/i) != -1)
		fileLineFeed = "windows";
	else
		fileLineFeed = "macintosh";
	// set linefeed
	fileOut.linefeed = fileLineFeed;

	// open for write
	fileOut.open("w", "TEXT", "????");
	
	// write head
	fileOut.writeln("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	fileOut.writeln();
	
	//write imageset name, imagefile etc
	fileOut.writeln("<Imageset Name=\"" + imageName + "\" Imagefile=\"" + imageFile + "\" NativeHorzRes=\"" + nativeHorzRes + "\" NativeVertRes=\"" + nativeVertRes + "\" AutoScaled=\"" + autoScaled + "\" >");
	
	//write rows - components - images - layouts
	writeRows(app.activeDocument, fileOut);
	
	//write foot
	fileOut.writeln("</Imageset>");

	// close the file
	fileOut.close();
}

function writeRows(el, fileOut)
{
	// Get the layers
	var layers = el.layers;

	// Loop
	for (var layerIndex = layers.length; layerIndex > 0; layerIndex--)
	{
		// curentLayer ref
		var currentLayer = layers[layerIndex-1];
			
		// currentLayer is a LayerSet
		if (currentLayer.typename == "LayerSet") {
			writeRows(currentLayer, fileOut);
				
		// currentLayer is not a LayerSet, but it's ArtLayer
		} else {
			if (currentLayer.visible){
				xPos = currentLayer.bounds[0].value;
				yPos = currentLayer.bounds[1].value;
				width = currentLayer.bounds[2].value - currentLayer.bounds[0].value; 
				height = currentLayer.bounds[3].value - currentLayer.bounds[1].value;
				
				//<Image Name="ButtonOk" XPos="490" YPos="0" Width="59" Height="50" />
				fileOut.writeln ("\t<Image Name=\"" + currentLayer.name + "\" XPos=\"" + xPos +  "\" YPos=\"" + yPos +  "\" Width=\"" + width +  "\" Height=\"" + height +"\" />"); 
			}
		}
	}	
}


function showDialog() 
{
    dlgMain = new Window("dialog",  scriptName);

	dlgMain.orientation = 'column';
	dlgMain.alignChildren = 'left';
	
	// first row
	dlgMain.grpFirstRow = dlgMain.add("group");
	dlgMain.grpFirstRow.orientation = 'row';
	dlgMain.grpFirstRow.alignChildren = 'top';
	dlgMain.grpFirstRow.alignment = 'fill';

	dlgMain.grpFirstRowLeft = dlgMain.grpFirstRow.add("group");
	dlgMain.grpFirstRowLeft.orientation = 'column';
	dlgMain.grpFirstRowLeft.alignChildren = 'left';
	dlgMain.grpFirstRowLeft.alignment = 'center';

	dlgMain.grpFirstRowRight = dlgMain.grpFirstRow.add("group");
	dlgMain.grpFirstRowRight.orientation = 'column';
	dlgMain.grpFirstRowRight.alignChildren = 'left';
	dlgMain.grpFirstRowRight.alignment = 'center';
	
	// second row
	dlgMain.grpSecondRow = dlgMain.add("group");
	dlgMain.grpSecondRow.orientation = 'row';
	dlgMain.grpSecondRow.alignChildren = 'top';
	dlgMain.grpSecondRow.alignment = 'right';

	dlgMain.grpSecondRowLeft = dlgMain.grpSecondRow.add("group");
	dlgMain.grpSecondRowLeft.orientation = 'column';
	dlgMain.grpSecondRowLeft.alignChildren = 'right';
	dlgMain.grpSecondRowLeft.alignment = 'center';

	dlgMain.grpSecondRowRight = dlgMain.grpSecondRow.add("group");
	dlgMain.grpSecondRowRight.orientation = 'column';
	dlgMain.grpSecondRowRight.alignChildren = 'right';
	dlgMain.grpSecondRowRight.alignment = 'center';

	// third row
	dlgMain.grpThirdRow = dlgMain.add("group");
	dlgMain.grpThirdRow.orientation = 'row';
	dlgMain.grpThirdRow.alignChildren = 'top';
	dlgMain.grpThirdRow.alignment = 'right';

	dlgMain.grpThirdRowLeft = dlgMain.grpThirdRow.add("group");
	dlgMain.grpThirdRowLeft.orientation = 'column';
	dlgMain.grpThirdRowLeft.alignChildren = 'right';
	dlgMain.grpThirdRowLeft.alignment = 'center';

	dlgMain.grpThirdRowRight = dlgMain.grpThirdRow.add("group");
	dlgMain.grpThirdRowRight.orientation = 'column';
	dlgMain.grpThirdRowRight.alignChildren = 'right';
	dlgMain.grpThirdRowRight.alignment = 'center';

	// fourth row
	dlgMain.grpFourthRow = dlgMain.add("group");
	dlgMain.grpFourthRow.orientation = 'row';
	dlgMain.grpFourthRow.alignChildren = 'top';
	dlgMain.grpFourthRow.alignment = 'right';

	dlgMain.grpFourthRowLeft = dlgMain.grpFourthRow.add("group");
	dlgMain.grpFourthRowLeft.orientation = 'column';
	dlgMain.grpFourthRowLeft.alignChildren = 'right';
	dlgMain.grpFourthRowLeft.alignment = 'center';

	dlgMain.grpFourthRowRight = dlgMain.grpFourthRow.add("group");
	dlgMain.grpFourthRowRight.orientation = 'column';
	dlgMain.grpFourthRowRight.alignChildren = 'right';
	dlgMain.grpFourthRowRight.alignment = 'center';

	// fifth row
	dlgMain.grpFifthRow = dlgMain.add("group");
	dlgMain.grpFifthRow.orientation = 'row';
	dlgMain.grpFifthRow.alignChildren = 'top';
	dlgMain.grpFifthRow.alignment = 'right';

	dlgMain.grpFifthRowLeft = dlgMain.grpFifthRow.add("group");
	dlgMain.grpFifthRowLeft.orientation = 'column';
	dlgMain.grpFifthRowLeft.alignChildren = 'right';
	dlgMain.grpFifthRowLeft.alignment = 'center';

	dlgMain.grpFifthRowRight = dlgMain.grpFifthRow.add("group");
	dlgMain.grpFifthRowRight.orientation = 'column';
	dlgMain.grpFifthRowRight.alignChildren = 'right';
	dlgMain.grpFifthRowRight.alignment = 'center';
	
	// last row - OK, CANCEL
	dlgMain.grpLastRow = dlgMain.add("group");
	dlgMain.grpLastRow.orientation = 'row';
	dlgMain.grpLastRow.alignChildren = 'top';
	dlgMain.grpLastRow.alignment = 'right';

	dlgMain.grpLastRowLeft = dlgMain.grpLastRow.add("group");
	dlgMain.grpLastRowLeft.orientation = 'column';
	dlgMain.grpLastRowLeft.alignChildren = 'left';
	dlgMain.grpLastRowLeft.alignment = 'fill';

	dlgMain.grpLastRowRight = dlgMain.grpLastRow.add("group");
	dlgMain.grpLastRowRight.orientation = 'column';
	dlgMain.grpLastRowRight.alignChildren = 'right';
	dlgMain.grpLastRowRight.alignment = 'top';

	// LEFT SIDE
	dlgMain.grpFirstRowLeft.add("statictext", undefined, "Imageset name:");
	dlgMain.grpSecondRowLeft.add("statictext", undefined, "Imagefile:");
	dlgMain.grpThirdRowLeft.add("statictext", undefined, "NativeHorzRes:");
	dlgMain.grpFourthRowLeft.add("statictext", undefined, "NativeVertRes:");
	dlgMain.grpFifthRowLeft.add("statictext", undefined, "AutoScaled:");
	dlgMain.btnOk = dlgMain.grpLastRowLeft.add("button", undefined, "Ok" );
    dlgMain.btnOk.onClick = btnOkOnClick;

		// RIGHT SIDE
	dlgMain.etName = dlgMain.grpFirstRowRight.add("edittext", undefined, app.activeDocument.name);
    dlgMain.etName.preferredSize.width = 150;
	dlgMain.etFile = dlgMain.grpSecondRowRight.add("edittext", undefined, app.activeDocument.name + ".png");
    dlgMain.etFile.preferredSize.width = 150;
	dlgMain.etNativeHorzRes = dlgMain.grpThirdRowRight.add("edittext", undefined, "1024");
    dlgMain.etNativeHorzRes.preferredSize.width = 150;
	dlgMain.etNativeVertRes = dlgMain.grpFourthRowRight.add("edittext", undefined, "768");
    dlgMain.etNativeVertRes.preferredSize.width = 150;
	dlgMain.etAutoScaled = dlgMain.grpFifthRowRight.add("edittext", undefined, "true");
    dlgMain.etAutoScaled.preferredSize.width = 150;
	dlgMain.btnCancel = dlgMain.grpLastRowRight.add("button", undefined, "Cancel" );
    dlgMain.btnCancel.onClick = function() { 
		var d = this;
		while (d.type != 'dialog') {
			d = d.parent;
		}
		d.close(cancelButtonID); 
	}

	dlgMain.defaultElement = dlgMain.btnOk;
	dlgMain.cancelElement = dlgMain.btnCancel;

    // in case we double clicked the file
    app.bringToFront();

    dlgMain.center();

    var result = dlgMain.show();
    if (cancelButtonID == result) {
		return result;
	}
    return result;
}


function btnOkOnClick()
{
	imageName = dlgMain.etName.text;
	imageFile = dlgMain.etFile.text;
	nativeHorzRes= dlgMain.etNativeHorzRes.text;
	nativeVertRes = dlgMain.etNativeVertRes.text;
	autoScaled = dlgMain.etAutoScaled.text;

	// find the dialog in this auto layout mess
	var d = this;
	while (d.type != 'dialog') {
		d = d.parent;
	}
	d.close(okButtonID);
}
