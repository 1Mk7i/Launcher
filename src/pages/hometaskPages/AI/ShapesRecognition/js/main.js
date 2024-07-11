window.onload=function(){

	console.log("Hello")
	let canvas = document.getElementById("myCanvas");
	window.ctx = canvas.getContext("2d", {willReadFrequently:true});
	window.isPointerDownNow = false
	canvas.addEventListener("pointerdown", onCanvasPointerDown)
	canvas.addEventListener("pointermove", onCanvasPointerMove)
	canvas.addEventListener("pointerup", onCanvasPointerUp)
	document.addEventListener("keydown", onkeyDown)

	window.network = new NeuroNet()
	window.network.createIntroLayer(28*28);

	window.network.createLayer(500,"sigmoid");
	window.network.createLayer(10,"sigmoid");

	for (let k=0; k<10000; k++){
		let pictureTypeId=Math.floor(Math.random()*10)
		let corAnswers=[0,0,0,0,0,0,0,0,0,0]
		corAnswers[pictureTypeId]=1;

		switch (pictureTypeId){
			case 0:{
				drawRoman1();
				break;
			}
			case 1:{
				drawRoman2();
				break;
			}
			case 2:{
				drawRoman3();
				break;
			}
			case 3:{
				drawRoman4();
				break;
			}
			case 4:{
				drawRoman5();
				break;
			}
			case 5:{
				drawRoman6();
				break;
			}
			case 6:{
				drawRoman7();
				break;
			}
			case 7:{
				drawRoman8();
				break;
			}
			case 8:{
				drawRoman9();
				break;
			}
			case 9:{
				drawRoman10();
				break;
			}
		}

		let neuronInputs = getNeuroInputsFromCanvas()

		window.network.calculateOutsForInputs(neuronInputs);
		let corAr=[0,0,0,0,0,0,0,0,0,0]
		corAr[pictureTypeId]=1;
		window.network.calculateErrors(corAr)
		window.network.adjustParams(0.01)
		
		if (window.network.findIdOfMostActivatedOutNeuron()==pictureTypeId){
			numCorrects++
		}
		if (k%reportingStep==0){
			console.log(k, pictureTypeId, window.network.getOutputs(),numCorrects/reportingStep)
			numCorrects=0
		}
	}

}


//Щоб навчити мережу відрізняти вертикальну лінію від горизонтальної, треба:
/*
0. визначаємо, якого типу лінію малювати (вертикальну чи горизонтальну)
1. малюємо на ctx лінію (вертикальну чи шгорищонтальну) - товщини 1-5 пікс, відхилення від перпендикіляру - до 10%
2. довжина лінії - не менше 14 пікс
3. значення колькорів з канвасу подамо на вхід мережі
4. навчаємо мережу
*/

//малювання випадкової вертикальної лінії

//Коли зробите розпізнавання ліній, додайте розпізнавання діагональних ліній, нахилених право та вліво
//(що займають дорівнюють від половини до повної діагоналі всього поля
//та зробіть нейромережу, яка б розрізняла всі 4 форми
//Коли зробите розпізнавання ліній, додайте ще 2 функції: малювання випадковго квадрата (зі стороною від 14 до 28 пікселів)
//та малювання випадкового кола: (з радіусом від 14 до 28 пікселів)
//та зробіть нейромережу, яка б розрізняла всі 6 форм
//придумайте ще форми, які можна малювати та навчити мережу відрізняти

function drawVerticalLine(){
	window.ctx.fillStyle="#000000"
	window.ctx.fillRect(0,0,28,28)

	let x = Math.floor(Math.random()*28)+1
	let y = Math.floor(Math.random()*28)+1
	let len = Math.floor(Math.random()*14)+14
	// нахилена лінія від -20% до +20%
	let w = Math.floor(Math.random()*5)-2

	let x1 = x+w
	let y1 = y+len

	if (y1<0 || y1>28){
		y1=0
	}
	if (x1<0 || x1>28){
		x1=0
	}

	window.ctx.beginPath()
	window.ctx.strokeStyle="#ffffff"
	window.ctx.moveTo(x,y)
	window.ctx.lineTo(x1,y1)
	window.ctx.stroke()
}

function drawHorizontalLine(){
	window.ctx.fillStyle="#000000"
	window.ctx.fillRect(0,0,28,28)

	let x = Math.floor(Math.random()*28)
	let y = Math.floor(Math.random()*28)
	let len = Math.floor(Math.random()*14)+14
	let w = Math.floor(Math.random()*5)-2

	let x1 = x+len
	let y1 = y+w

	if (y1<0 || y1>28){
		y1=0
	}
	if (x1<0 || x1>28){
		x1=0
	}

	window.ctx.beginPath()
	window.ctx.strokeStyle="#ffffff"
	window.ctx.moveTo(x,y)
	window.ctx.lineTo(x1,y1)
	window.ctx.stroke()

}

function drawDiagonalLine(){
	window.ctx.fillStyle="#000000"
	window.ctx.fillRect(0,0,28,28)

	let x = Math.floor(Math.random()*28)
	let y = Math.floor(Math.random()*28)
	let len = Math.floor(Math.random()*14)+14

	let x1 = x+len
	let y1 = y+len

	if (y1<0 || y1>28){
		y1=0
	}
	if (x1<0 || x1>28){
		x1=0
	}

	window.ctx.beginPath()
	window.ctx.strokeStyle="#ffffff"
	window.ctx.moveTo(x,y)
	window.ctx.lineTo(x1,y1)
	window.ctx.stroke()

}

function drawSquare(){
	window.ctx.fillStyle="#000000"
	window.ctx.fillRect(0,0,28,28)

	let x = Math.floor(Math.random()*28)
	let y = Math.floor(Math.random()*28)
	let len = Math.floor(Math.random()*14)+14

	if (y+len>28){
		len = 28-y
	}
	if (x+len>28){
		len = 28-x
	}

	window.ctx.beginPath()
	window.ctx.fillStyle="#ffffff"
	window.ctx.moveTo(x,y)
	window.ctx.lineTo(x+len,y)
	window.ctx.lineTo(x+len,y+len)
	window.ctx.lineTo(x,y+len)
	window.ctx.lineTo(x,y)
	window.ctx.fill()
}

function drawCircle(){
	window.ctx.fillStyle="#000000"
	window.ctx.fillRect(0,0,28,28)

	let x = Math.floor(Math.random()*28)
	let y = Math.floor(Math.random()*28)
	let r = Math.floor(Math.random()*14)+14

	if (y+r>28){
		r = 28-y
	}
	if (x+r>28){
		r = 28-x
	}

	window.ctx.beginPath()
	window.ctx.strokeStyle="#ffffff"
	window.ctx.arc(x,y,r,0,2*Math.PI)
	window.ctx.stroke()
}
// малювання римських цифр
function drawRoman1() {
    window.ctx.fillStyle="#000000"
    window.ctx.fillRect(0,0,28,28)
	// 1
	x0 = 3+Math.floor(Math.random()*25)
	l = 14+Math.floor(Math.random()*14)
	y0 = 1+Math.floor(Math.random()*(28-l))
	x1 = Math.floor(x0+(0.05*28-Math.random()*0.1*28))
	window.ctx.beginPath()
	window.ctx.strokeStyle = "#ffffff";
	window.ctx.moveTo(x0,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
}

function drawRoman2() {
    window.ctx.fillStyle="#000000"
    window.ctx.fillRect(0,0,28,28)
	//2

	x0 = 2+Math.floor(Math.random()*12)
	l = 14+Math.floor(Math.random()*14)
	y0 = 1+Math.floor(Math.random()*(28-l))
	x1 = Math.floor(x0+(0.05*28-Math.random()*0.1*28))
	window.ctx.beginPath()
	window.ctx.strokeStyle = "#ffffff";
	window.ctx.moveTo(x0,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	x1 = Math.floor(x0+(0.05*28-Math.random()*0.1*28))
	window.ctx.moveTo(Math.floor(x0+0.2*28 + Math.random()*28*0.2),y0)
	window.ctx.lineTo(Math.floor(x1+0.2*28 + Math.random()*28*0.2) - Math.random()*28*0.05,y0+l)
	window.ctx.stroke()
}

function drawRoman3() {
    window.ctx.fillStyle="#000000"
    window.ctx.fillRect(0,0,28,28)
	// 3
	x0 = 1+Math.floor(Math.random()*6)
	l = 14+Math.floor(Math.random()*14)
	y0 = 1+Math.floor(Math.random()*(28-l))
	x1 = Math.floor(x0+(0.05*28-Math.random()*0.1*28))
	space = 0.25*28
	window.ctx.beginPath()
	window.ctx.strokeStyle = "#ffffff";
	window.ctx.moveTo(x0,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	x1 = Math.floor(x0+(0.05*28-Math.random()*0.1*28))
	window.ctx.moveTo(Math.floor(x0+space),y0)
	window.ctx.lineTo(Math.floor(x1+space),y0+l)
	window.ctx.stroke()
	x1 = Math.floor(x0+(0.05*28-Math.random()*0.1*28))
	window.ctx.moveTo(Math.floor(x0+(space*2)),y0)
	window.ctx.lineTo(Math.floor(x1+(space*2) + Math.random()*28*0.05), y0+l)
	window.ctx.stroke()
}

function drawRoman4() {
    window.ctx.fillStyle = "#000000";
    window.ctx.fillRect(0, 0, 28, 28);
	// 4
	x0 = 1+Math.floor(Math.random()*6)
	l = 14+Math.floor(Math.random()*14)
	y0 = 1+Math.floor(Math.random()*(28-l))
	x1 = Math.floor(x0+(0.05*28-Math.random()*0.1*28))
	space = 0.25*28
	window.ctx.beginPath()
	window.ctx.strokeStyle = "#ffffff";
	window.ctx.moveTo(x0,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	x1 = Math.floor(x0+(0.05*28+Math.random()*0.1*28)+space)
	window.ctx.moveTo(x0+space,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	window.ctx.moveTo(x1,y0+l)
	x1 = Math.floor(x0+(0.05*28-Math.random()*0.1*28)+(space*2))
	window.ctx.lineTo(Math.floor(x1 + Math.random()*28*0.1), y0)
	window.ctx.stroke()
}

function drawRoman5() {
	window.ctx.fillStyle = "#000000";
	window.ctx.fillRect(0, 0, 28, 28);
	//5
	x0 = 1+Math.floor(Math.random()*10)
	l = 14+Math.floor(Math.random()*14)
	y0 = 1+Math.floor(Math.random()*(28-l))
	x1 = Math.floor(x0+(0.1*28+Math.random()*0.2*28))
	window.ctx.beginPath()
	window.ctx.strokeStyle = "#ffffff";
	window.ctx.moveTo(x0,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	window.ctx.moveTo(x1,y0+l)
	window.ctx.lineTo(Math.floor(x1 + Math.random()*28*0.2),y0)
	window.ctx.stroke()
}

function drawRoman6() {
	window.ctx.fillStyle = "#000000";
	window.ctx.fillRect(0, 0, 28, 28);
	// 6
	x0 = 2+Math.floor(Math.random()*5)
	l = 10+Math.floor(Math.random()*14)
	y0 = 1+Math.floor(Math.random()*(28-l))
	x1 = Math.floor(x0+(0.1*28+Math.random()*0.2*28))
	space = 0.25*28
	window.ctx.beginPath()
	window.ctx.strokeStyle = "#ffffff";
	window.ctx.moveTo(x0,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	window.ctx.moveTo(x1,y0+l)
	x0 = Math.floor(x1 + Math.random()*28*0.2)
	window.ctx.lineTo(Math.floor(x0 + Math.random()*28*0.1),y0)
	window.ctx.stroke()
	window.ctx.moveTo(Math.floor(x0 + 28*0.2),y0)
	window.ctx.lineTo(Math.floor(x0 + 28*0.3 - Math.random()*28*0.2),y0+l)
	window.ctx.stroke()
}

function drawRoman7() {
    window.ctx.fillStyle = "#000000";
    window.ctx.fillRect(0, 0, 28, 28);
	// 7
	x0 = 2+Math.floor(Math.random()*5)
	l = 8+Math.floor(Math.random()*14)
	y0 = 1+Math.floor(Math.random()*(28-l))
	x1 = Math.floor(x0+(0.1*28+Math.random()*0.2*28))
	space = 0.2*28
	window.ctx.beginPath()
	window.ctx.strokeStyle = "#ffffff";
	window.ctx.moveTo(x0,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	window.ctx.moveTo(x1,y0+l)
	x0 = Math.floor(x1 + Math.random()*28*0.2)
	window.ctx.lineTo(Math.floor(x0 + Math.random()*28*0.1),y0)
	window.ctx.stroke()
	window.ctx.moveTo(Math.floor(x0 + space),y0)
	window.ctx.lineTo(Math.floor(x0 + space - Math.random()*28*0.1),y0+l)
	window.ctx.stroke()
	window.ctx.moveTo(Math.floor(x0 + space + (space/1.5)),y0)
	window.ctx.lineTo(Math.floor(x0 + (space *2 ) - Math.random()*space/2),y0+l)
	window.ctx.stroke()
}


function drawRoman8() {
    window.ctx.fillStyle = "#000000";
    window.ctx.fillRect(0, 0, 28, 28);
	// 8
	x0 = 2+Math.floor(Math.random()*3)
	l = 6+Math.floor(Math.random()*14)
	y0 = 1+Math.floor(Math.random()*(28-l))
	x1 = Math.floor(x0+(0.05*28+Math.random()*0.1*28))
	space = 0.2*28
	window.ctx.beginPath()
	window.ctx.strokeStyle = "#ffffff";
	window.ctx.moveTo(x0,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	window.ctx.moveTo(x1,y0+l)
	x0 = Math.floor(x1 + Math.random()*28*0.2)
	window.ctx.lineTo(Math.floor(x0 + Math.random()*28*0.1),y0)
	window.ctx.stroke()
	window.ctx.moveTo(Math.floor(x0 + space),y0)
	window.ctx.lineTo(Math.floor(x0 + space - Math.random()*28*0.1),y0+l)
	window.ctx.stroke()
	window.ctx.moveTo(Math.floor(x0 + space + (space/1.5)),y0)
	window.ctx.lineTo(Math.floor(x0 + (space *2 ) - Math.random()*space/2),y0+l)
	window.ctx.stroke()
	window.ctx.moveTo(Math.floor(x0 + space +space + (space/1.5)),y0)
	window.ctx.lineTo(Math.floor(x0 + (space *3 ) - Math.random()*space/2),y0+l)
	window.ctx.stroke()
}

function drawRoman9() {
    window.ctx.fillStyle = "#000000";
    window.ctx.fillRect(0, 0, 28, 28);
	// 9
	x0 = 2+Math.floor(Math.random()*8)
	l = 8+Math.floor(Math.random()*14)
	y0 = 1+Math.floor(Math.random()*(28-l))
	x1 = Math.floor(x0+(0.05*28-Math.random()*0.1*28))
	space = 0.2*28
	window.ctx.beginPath()
	window.ctx.strokeStyle = "#ffffff";
	window.ctx.moveTo(x0,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	x0 = Math.floor(x0 + space)
	x1 = Math.floor(x0+(0.25*28+Math.random()*0.1*28))
	window.ctx.moveTo(Math.floor(x0),y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	window.ctx.moveTo(Math.floor(x0 + 28*0.05 - Math.random()*28*0.1),y0+l)
	window.ctx.lineTo(Math.floor(x1 + 28*0.05 - Math.random()*28*0.1),y0)
	window.ctx.stroke()
}

function drawRoman10() {
    window.ctx.fillStyle = "#000000";
    window.ctx.fillRect(0, 0, 28, 28);

	// 10
	x0 = 2+Math.floor(Math.random()*10)
	l = 8+Math.floor(Math.random()*14)
	y0 = 1+Math.floor(Math.random()*(28-l))
	x1 = Math.floor(x0+(0.25*28+Math.random()*0.1*28))
	space = 0.2*28
	window.ctx.beginPath()
	window.ctx.strokeStyle = "#ffffff";
	window.ctx.moveTo(x0,y0)
	window.ctx.lineTo(x1,y0+l)
	window.ctx.stroke()
	window.ctx.moveTo(Math.floor(x0 + 28*0.05 - Math.random()*28*0.1),y0+l)
	window.ctx.lineTo(Math.floor(x1 + 28*0.05 - Math.random()*28*0.1),y0)
	window.ctx.stroke()
}

function getNeuroInputsFromCanvas(){
	let imageData = window.ctx.getImageData(0, 0, 28, 28);
	return loadImage2Array(imageData)//ось це подамо на вхід нейромережі
}

function checkNeuronNetRecognition(){

}


var reportingStep=100;
var numCorrects=0

function loadImage2Array(imageData){
	let res=[];
	for (let i=0; i<28*28; i++){
		res.push(imageData.data[i*4])
	}
	return res;
}

function recognizeImageFromCanvas(){
	window.network.calculateOutsForInputs(getNeuroInputsFromCanvas())
	console.log(window.network.getOutputs())
	PrintText()
}

function onCanvasPointerDown(evt){
	window.isPointerDownNow = true
	// console.log("onCanvasPointerDown",evt)
	if (evt.altKey){
		window.ctx.fillStyle="#000000"
		window.ctx.fillRect(0,0,28,28)
	}
}

function onCanvasPointerMove(evt){
	// console.log("onCanvasPointerMove",evt)
	if (window.isPointerDownNow){
		if (evt.shiftKey){
			window.ctx.fillStyle="#000000"
		}else{
			window.ctx.fillStyle="#ffffff"
		}
		
		let w = 1;
		if (evt.ctrlKey){
			w=2
		}
		window.ctx.fillRect(evt.offsetX-w*0.5,evt.offsetY-w*0.5,w,w)
	}
}

function onCanvasPointerUp(evt){
	// console.log("onCanvasPointerUp",evt)
	window.isPointerDownNow = false
}

function onkeyDown(evt){
	if (evt.key === 'h' || evt.key === 'H') {
		drawHorizontalLine();
	} else if (evt.key === 'v' || evt.key === 'V') {
		drawVerticalLine();
	} else if (evt.key === 'r' || evt.key === 'R') {
		recognizeImageFromCanvas();
	} else if (evt.key === 'd' || evt.key === 'D') {
		drawDiagonalLine();
	} else if (evt.key === 's' || evt.key === 'S') {
		drawSquare();
	} else if (evt.key === 'c' || evt.key === 'C') {
		drawCircle();
	} else if (evt.key === '1') {
		drawRoman1();
	} else if (evt.key === '2') {
		drawRoman2();
	} else if (evt.key === '3') {
		drawRoman3();
	} else if (evt.key === '4') {
		drawRoman4();
	} else if (evt.key === '5') {
		drawRoman5();
	} else if (evt.key === '6') {
		drawRoman6();
	} else if (evt.key === '7') {
		drawRoman7();
	} else if (evt.key === '8') {
		drawRoman8();
	} else if (evt.key === '9') {
		drawRoman9();
	} else if (evt.key === '0') {
		drawRoman10();
	}
}

function PrintText(){
	let corAr = window.network.getOutputs();
	let sortCorAr=corAr.slice().sort((a,b)=>b-a)
	for (let i=0; i<5; i++){
		// if (corAr[0]===sortCorAr[0]){
		// 	console.log("It is a vertical line")
		// }
		// if (corAr[1]===sortCorAr[0]){
		// 	console.log("It is a horizontal line")
		// }
		// if (corAr[2]===sortCorAr[0]){
		// 	console.log("It is a diagonal line")
		// }
		// if (corAr[3]===sortCorAr[0]){
		// 	console.log("It is a square")
		// }
		// if (corAr[4]===sortCorAr[0]){
		// 	console.log("It is a circle")
		// }
		if (corAr[0]===sortCorAr[0]){
			console.log("It is a Roman 1")
		}
		if (corAr[1]===sortCorAr[0]){
			console.log("It is a Roman 2")
		}
		if (corAr[2]===sortCorAr[0]){
			console.log("It is a Roman 3")
		}
		if (corAr[3]===sortCorAr[0]){
			console.log("It is a Roman 4")
		}
		if (corAr[4]===sortCorAr[0]){
			console.log("It is a Roman 5")
		}
		if (corAr[5]===sortCorAr[0]){
			console.log("It is a Roman 6")
		}
		if (corAr[6]===sortCorAr[0]){
			console.log("It is a Roman 7")
		}
		if (corAr[7]===sortCorAr[0]){
			console.log("It is a Roman 8")
		}
		if (corAr[8]===sortCorAr[0]){
			console.log("It is a Roman 9")
		}
		if (corAr[9]===sortCorAr[0]){
			console.log("It is a Roman 10")
		}
	}
}