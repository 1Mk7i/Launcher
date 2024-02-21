class World {
	constructor(){
		this.bots=[]
	}

	startTournament(botsClasses, numGames, showLog=false){
		this.bots.length=0;
		//створюємо ботів для турніра
		for (let i=0; i<botsClasses.length; i++){
			let b = new botsClasses[i](botsClasses[i].name+"_"+i);
			this.bots.push(b)
		}
		this.tournamentScores={}

		for (let i=0; i<numGames; i++){
			this.startGame(showLog)
		}
		console.log("Tournament results:", this.tournamentScores)
		
		this.displayResults()
	}

	displayResults(worldName) {
		let info = document.querySelector(".info");
		let tournamentResults = document.createElement("div");
		tournamentResults.classList.add("tournament-results");

		let worldNameElement = document.createElement("h4");
		worldNameElement.classList.add("world-name");
		worldNameElement.textContent = this.constructor.name;
		tournamentResults.appendChild(worldNameElement);

		let sortedBots = Object.entries(this.tournamentScores).sort((a, b) => b[1] - a[1]);
		for (let i = 0; i < sortedBots.length; i++) {
			let botName = sortedBots[i][0];
			let botScore = sortedBots[i][1];
			let result = document.createElement("div");
			result.classList.add("result");
			result.innerHTML = (i + 1) + ". " + botName + " : " + botScore;
			tournamentResults.appendChild(result);
		}

		info.appendChild(tournamentResults);
	}


	startGame(showLog=true){
		//боти вже є
		this.initNewGamePosition();

		this.randomizeMoveOrder();

		this.informBotsOfGameStart()

		//доки гра не закінчена, робимо ходи
		let currentBotId = 0;
		while(!this.isGameOver()){//ходи продовжуємо, поки гра триває
			//будуємо ситуація для показу боту
			let ob = this.buildCurrentGameSituation()
			if (showLog)console.log("Situation ",ob)
			//який бот зараз ходить
			if (showLog)console.log("Bot ",currentBotId, "moves")
			let bot = this.bots[currentBotId]
			//показуємо боту ситуація та отримуємо від нього хід
			let botMove = bot.makeMoveForSituation(ob)
			if (showLog)console.log("Bot Move: ",botMove)
			//якщо хід задовольняє правилам
			if (this.validateMove(botMove)){
				//виконуємо цей хід
				this.makeBotMove(botMove);
				//якщо хід привів до завершення гри
				if (this.isGameOver()){
					//визначаємо, хто виграв, хто програв
					this.calculateGamePoints(currentBotId)
				}else{
					//якщо ні, визначаємо наступного гравця, який буде ходити
					currentBotId++;
					currentBotId%=this.bots.length
				}
			}else{
				//якщо хід не задовольняє правилам, то зупиняємо гру, зарахувавши боту програш
				this.stopGameAfterBotError(currentBotId);
				break;
			}
		}
	}

	initNewGamePosition(){
	
	}
	//задаємо випадкову чергу ходів
	randomizeMoveOrder(){
		for (let i=0; i<this.bots.length-1; i++){
			//пробігаємо по свсіх елементах масиву
			//та міняємо місцями з випадковим елементом від даного (включаючи) до кінця
			let j = i+Math.floor(Math.random()*(this.bots.length-i))
			let t = this.bots[i]
			this.bots[i]=this.bots[j]
			this.bots[j]=t
		}		
	}

	isGameOver(){
		return false;
	}
	makeBotMove(moveOb){
	
	}
	stopGameAfterBotError(botId){
	
	}
	validateMove(moveOb){
		return true
	}
	buildCurrentGameSituation(){
		return {}
	}

	calculateGamePoints(currentBotId){
	
	}

	informBotsOfGameStart(){
		for (let i=0; i<this.bots.length; i++){
			let bot = this.bots[i];
			bot.getInformedOfGameStart();
		}
	}
	//дати перемогу у грі боту з індексом botId
	giveVictoryToSingleBot(botId){
		for (let i=0; i<this.bots.length; i++){
			let bot = this.bots[i];
			if (i==botId){
				if (this.tournamentScores[bot.myName]){
					this.tournamentScores[bot.myName]++
				}else{
					this.tournamentScores[bot.myName]=1
				}
				bot.getInformedOfVictory()
			}else{
				bot.getInformedOfDefeat()
			}
		}
	}
	//дати перемогу у грі усім ботам окрім бота з індексом botId
	giveDefeatToSingleBot(botId){
		for (let i=0; i<this.bots.length; i++){
			let bot = this.bots[i];
			if (i!=botId){
				if (this.tournamentScores[bot.myName]){
					this.tournamentScores[bot.myName]++
				}else{
					this.tournamentScores[bot.myName]=1
				}	
				bot.getInformedOfVictory()		
			}else{
				bot.getInformedOfDefeat()
			}
		}	
	}
}
//що має вміти ігровий світ?
//влаштовувати турнір між ботами
//турнір складаєть з кількох ігор
	//кожна гра складається з:
	//генерується випадкове початкове число
	//ініцалізуються боти, їх задається випадкова черга ходу
	//відповідно черги ходу ботам повідомляється поточна ігрова ситуація 
	//на яку бот відповідає ходом, який хоче зробити
	//світ перевіряє, чи підпадає хід під правила гри
	//якщо так, то хід робиться, змінюється ігрова ситуація та хід переходить до наступного боту
	//якщо ні, є 2 варіанти дій: а) зробити допустимий хід, якомога ближче до того, який бажає бот
	//б) при некоректному ході зарахувати програш
	//гра продовжується, доки не настсне умова виграшу однієї за сторін
//після завершення гри оновлюємо результати ботів у турнірі
//після завершення турніру видаємо результати

class BachetWorld extends World{
	constructor(){
		super()
		console.log("BachetWorld created")

		this.N = 100;
	}

	isGameOver(){
		return this.N<=0;
	}

	//{n:1..3}
	makeBotMove(moveOb){
		this.N-=moveOb.n
	}
	//moveOb має бути {n:1..3}
	validateMove(moveOb){
		let res = true;
		if (moveOb["n"]){
			if (Math.floor(moveOb["n"])===moveOb["n"]){
				if (moveOb["n"]>=1 && moveOb["n"]<=3){
					if (moveOb["n"]<=this.N){
						res=true;
					}else{
						res=false;
					}
				}else{
					res=false;
				}
			}else{
				res=false;
			}
		}else{
			res=false;
		}

		return res
	}

	buildCurrentGameSituation(){
		return {N:this.N}
	}	

	initNewGamePosition(){
		this.N = Math.floor(50+Math.random()*50)
	}	

	calculateGamePoints(currentBotId){
		this.giveVictoryToSingleBot(currentBotId)
	}

	stopGameAfterBotError(botId){
		//перемога всім іншим
		this.giveDefeatToSingleBot(botId)
	}	
}


class BachetWorld134 extends World{
	constructor(){
		super()
		console.log("BachetWorld134 created")

		this.N = 100;
	}

	isGameOver(){
		return this.N<=0;
	}

	makeBotMove(moveOb){
		this.N-=moveOb.n
	}
	validateMove(moveOb){
		let res = true;
		if (moveOb["n"]){
			if (Math.floor(moveOb["n"])===moveOb["n"]){
				if (moveOb["n"]>=1 && moveOb["n"]<=4 && moveOb["n"]!=2){
					if (moveOb["n"]<=this.N){
						res=true;
					}else{
						res=false;
					}
				}else{
					res=false;
				}
			}else{
				res=false;
			}
		}else{
			res=false;
		}

		return res
	}

	buildCurrentGameSituation(){
		return {N:this.N}
	}	

	initNewGamePosition(){
		this.N = Math.floor(50+Math.random()*50)
	}	

	calculateGamePoints(currentBotId){
		this.giveVictoryToSingleBot(currentBotId)
	}

	stopGameAfterBotError(botId){
		//перемога всім іншим
		this.giveDefeatToSingleBot(botId)
	}	
}

class BachetWorld1234 extends World{
	constructor(){
		super()
		console.log("BachetWorld1234 created")


		this.N = 100;
	}

	isGameOver(){
		return this.N<=0;
	}

	makeBotMove(moveOb){
		this.N-=moveOb.n
	}
	validateMove(moveOb){
		let res = true;
		if (moveOb["n"]){
			if (Math.floor(moveOb["n"])===moveOb["n"]){
				if (moveOb["n"]>=1 && moveOb["n"]<=4){
					if (moveOb["n"]<=this.N){
						res=true;
					}else{
						res=false;
					}
				}else{
					res=false;
				}
			}else{
				res=false;
			}
		}else{
			res=false;
		}

		return res
	}

	buildCurrentGameSituation(){
		return {N:this.N}
	}	

	initNewGamePosition(){
		this.N = Math.floor(50+Math.random()*50)
	}	

	calculateGamePoints(currentBotId){
		this.giveVictoryToSingleBot(currentBotId)
	}

	stopGameAfterBotError(botId){
		//перемога всім іншим
		this.giveDefeatToSingleBot(botId)
	}	
}