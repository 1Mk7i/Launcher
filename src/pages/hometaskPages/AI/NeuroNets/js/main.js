window.onload=function(){
	console.log("Hello")

	let num_inputs = 8
	let num_outputs = 3
	window.network = new NeuroNet()
	window.network.createIntroLayer(num_inputs)
	window.network.createLayer(200);
	window.network.createLayer(10);
	window.network.createLayer(num_outputs);
	//якщо на вході мережі буде масив чисел input_arr, то який за номером вихіднй нейрон має бути активований?
	function findCorrectActivation(input_arr){
		let A1 = input_arr[0]
		let A2 = input_arr[1]
		let B1 = input_arr[2]
		let B2 = input_arr[3]
		let C1 = input_arr[4]
		let C2 = input_arr[5]
		let D1 = input_arr[6]
		let D2 = input_arr[7]
		return findPoint(A1,A2,B1,B2,C1,C2,D1,D2)
	}
	
	function findPointInCircle(x,y,r){ return (x*x + y*y <= r*r) ? 1 : 0 } // функція, яка визначає чи знаходиться точка в колі

	function findPoint(A1,A2,B1,B2,C1,C2,D1,D2){
		let ad = (((D2-A2)**2) + ((D1-A1)**2))**0.5
		let bd = (((D2-B2)**2) + ((D1-B1)**2))**0.5
		let cd = (((D2-C2)**2) + ((D1-C1)**2))**0.5

		let arr = [ad,bd,cd]
		arr.sort(function (a, b) {
			return a - b;
		  });

		for (let i=0; i<3;i++){
			if (arr[0] === ad){
				return 0
			} else if (arr[0] === bd){
				return 1
			} else if (arr[0] === cd){
				return 2
			}
		}
	}
	window.findPoint = findPoint
	let learningData=[];
	for (let i=0; i<10000; i++){
		let A1 = Math.random()*50
		let A2 = Math.random()*50
		let B1 = Math.random()*50
		let B2 = Math.random()*50
		let C1 = Math.random()*50
		let C2 = Math.random()*50
		let D1 = Math.random()*50
		let D2 = Math.random()*50
		let input_arr = [A1,A2,B1,B2,C1,C2,D1,D2]
		let correct_neuron_id = findCorrectActivation(input_arr)
		input_arr.push(correct_neuron_id)
		learningData.push(input_arr)
	}

	//тепер проганяємо цю навчальну вибірку по нейромережі 
	for (let i=0; i<learningData.length; i++){
		let dataAr = learningData[i];
		let input_arr = dataAr.slice(0,dataAr.length-1)
		let answer = dataAr[dataAr.length-1];
		window.network.calculateOutsForInputs(input_arr)
		let networkAnswer = window.network.findIdOfMostActivatedOutNeuron();
		let correctActivation = []
			for (let k=0; k<num_outputs; k++){
				correctActivation.push(0)
			}
		correctActivation[answer] = 1;
		window.network.calculateErrors(correctActivation);
		window.network.adjustParams(0.1)
	}

	let testingData=[];
	for (let i=0; i<10; i++){
		let A1 = Math.random()*50 
		let A2 = Math.random()*50
		let B1 = Math.random()*50
		let B2 = Math.random()*50
		let C1 = Math.random()*50
		let C2 = Math.random()*50
		let D1 = Math.random()*50
		let D2 = Math.random()*50
		let input_arr = [A1,A2,B1,B2,C1,C2,D1,D2]
		let correct_neuron_id = findCorrectActivation(input_arr)
		input_arr.push(correct_neuron_id)
		testingData.push(input_arr)
	}

	let numCorrectAnswers=0;
	let numErrors=0;
	for (let i=0; i<testingData.length; i++){
		let dataAr = learningData[i];
		let input_arr = dataAr.slice(0,dataAr.length-1)
		let answer = dataAr[dataAr.length-1];
		window.network.calculateOutsForInputs(input_arr)
		let networkAnswer = window.network.findIdOfMostActivatedOutNeuron();

		if (answer==networkAnswer){
			numCorrectAnswers++
		}else{
			numErrors++
		}
	}
	console.log("correct percentage:",numCorrectAnswers/(numCorrectAnswers+numErrors))
}