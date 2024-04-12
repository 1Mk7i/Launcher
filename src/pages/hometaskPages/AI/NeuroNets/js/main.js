window.onload=function(){
	console.log("Hello")
	//створимо нейромережу та навчимо її визначати номер координатної чверті точки, що задаватиметься прою координат, х,у
	//у мережі має бути 2 входи (на один подаватимемо х, на другий у)
	//та 4 виходи (маэ активуватися нейрон, що выдповідатиме номеру чверті)
	window.network = new NeuroNet()
	window.network.createIntroLayer(3);
	window.network.createLayer(3);
	window.network.createLayer(3);


	function findMaxNumberId(a,b,c){
		let arr = [a,b,c]
		arr.sort(function (a, b) {return a - b;});
		if (arr[1]==a){
			return 0
		}
		if (arr[1]==b){
			return 1
		}
		if (arr[1]==c){
			return 2
		}
	}

	//будуємо навчальну вибірку
	let learningData=[];
	for (let i=0; i<10000; i++){
		let a = Math.random()*2-1
		let b = Math.random()*2-1
		let c = Math.random()*2-1
		learningData.push([a,b,c])
	}

	//тепер проганяємо цю навчальну вибірку по нейромережі 
	for (let i=0; i<learningData.length; i++){
		let dataAr = learningData[i];
		let a = dataAr[0];
		let b = dataAr[1];
		let c = dataAr[2];
		let answer = findMaxNumberId(a,b,c)
		window.network.calculateOutsForInputs([a,b,c])
		let networkAnswer = window.network.findIdOfMostActivatedOutNeuron();
		let correctActivation = [0,0,0];
		correctActivation[answer] = 1;
		window.network.calculateErrors(correctActivation);
		window.network.adjustParams(0.1)
	}

	//тепер треба перевірити, як мереда навчилася. Будуємо тестову вибірку
	let testingData=[];
	for (let i=0; i<10000; i++){
		let a = Math.random()*2-1
		let b = Math.random()*2-1
		let c = Math.random()*2-1
		testingData.push([a,b,c])
	}

	let numCorrectAnswers=0;
	let numErrors=0;
	for (let i=0; i<testingData.length; i++){
		let dataAr = testingData[i];
		let a = dataAr[0];
		let b = dataAr[1];
		let c = dataAr[2];
		let answer = findMaxNumberId(a,b,c)
		window.network.calculateOutsForInputs([a,b,c])
		let networkAnswer = window.network.findIdOfMostActivatedOutNeuron();

		if (answer==networkAnswer){
			numCorrectAnswers++
		}else{
			numErrors++
		}
	}
	console.log("correct percentage:",numCorrectAnswers/(numCorrectAnswers+numErrors))
}
