let char = 'B';
// масив останніх дій
let lastActions = [];
function updateLastActions() {
    if (lastActions.length > 5) {
        lastActions.shift();
    }
    let p = document.createElement("p");
    p.innerHTML = lastActions.join('<br>');
    // очищення вмісту
    document.getElementById('lastActions').innerHTML = '';
    document.getElementById('lastActions').appendChild(p);
}
function keepNoMoreThanKBestBotsOfClass() {
    window.world.keepNoMoreThanKBestBotsOfClass(EvoBot, 10);
    lastActions.push('keep 10 best');
    updateLastActions();
}
function createDescendantsOfBotsOfClass() {
    if (char.trim() !== '') { // Перевірка, чи не порожній рядок
        window.world.createDescendantsOfBotsOfClass(EvoBot, char);
        lastActions.push('create desc. of ' + char + ' class');
        updateLastActions();
    } else {
        console.error('Char is empty or undefined');
    }
}
function showAllBots() {
    console.log(window.world.allBots);
    window.world.displayAllBots();
    lastActions.push('showAllBots');
    updateLastActions();
}
function playTournaments(){
    window.world.startTournamentBetweenBots(window.world.allBots, 100, 2, false);
    lastActions.push('playTournaments');
    updateLastActions();
}
// функція для того щоб пройти декілька поколінь одразу
function createDescendantsOfBotsOfClassManyTimes(n) {
    let besyBot = window.world.allBotsResults[3];
    let lenght = window.world.allBotsResults.length;
    for (let i = 0; i < lenght; i++){
        if (besyBot >= i) {
        for (let i = 0; i < n; i++) {
            window.world.keepNoMoreThanKBestBotsOfClass(EvoBot, 10);
            window.world.createDescendantsOfBotsOfClass(EvoBot, "Skip"+i);
            window.world.startTournamentBetweenBots(window.world.allBots, 10, 2, false);
        }
        lastActions.push('create desc. ' + n + ' times');
        updateLastActions();
        }
        else {
            console.log('Error');
        }
    }
    
    
}

// функція для того щоб приховати статичну панель
let setn = 'off';

function hideStaticPanel(display) {
    if (display === 'off' && setn === 'on') {
        document.querySelector('.staticPanel').style.display = 'flex';
        setn = 'off';
    } else if (display === 'off' && setn === 'off') {
        document.querySelector('.staticPanel').style.display = 'none';
        setn = 'on';
    }
}


function getScore(rounds) {
    if (rounds === 0 || rounds === undefined || rounds === null || rounds === '' || rounds < 0 || rounds > 1000 || isNaN(rounds)) {
        document.getElementById('alert').style.display = 'block';
        setTimeout(() => {
            document.getElementById('alert').style.display = 'none';
        }, 3000);
    }else{
        let scores = [];
        for (let i = 0; i < rounds; i++) {
            console.log("ROUND_" + i);
            let evoRes = window.world.findAverageTournamentResultOfBotsOfClass(EvoBot);
            let modRes = window.world.findAverageTournamentResultOfBotsOfClass(EvoBotMod);
            let bestRes = window.world.findAverageTournamentResultOfBotsOfClass(Bot123);
            scores.push([evoRes / bestRes, modRes / bestRes]);
            window.world.keepNoMoreThanKBestBotsOfClass(EvoBot, 10);
            window.world.keepNoMoreThanKBestBotsOfClass(EvoBotMod, 10);
            window.world.createDescendantsOfBotsOfClass(EvoBot, "A" + i);
            window.world.createDescendantsOfBotsOfClass(EvoBotMod, "B" + i);
            window.world.startTournamentBetweenBots(window.world.allBots, 100, 2, false);
        }
        console.log(scores);

        // Побудова лінійного графіка
        let trace1 = {
            x: scores.map((score, index) => index), // раунди
            y: scores.map(score => score[0]), // значення для EvoBot
            mode: 'lines',
            type: 'scatter',
            name: 'EvoBot',
            line: {
                color: 'rgb(55, 128, 191)',
                width: 3
            }
        };

        let trace2 = {
            x: scores.map((score, index) => index), // раунди
            y: scores.map(score => score[1]), // значення для EvoBotMod
            mode: 'lines',
            type: 'scatter',
            name: 'EvoBotMod',
            line: {
                color: 'rgb(219, 64, 82)',
                width: 3
            }
        };

        let data = [trace1, trace2];

        let layout = {
            title: 'Графік',
            xaxis: {
                title: 'Раунд'
            },
            yaxis: {
                title: 'Значення'
            },
            legend: {
                x: 0.8,
                y: 1
            }
        };

        Plotly.newPlot('scatterPlot', data, layout);
    }
}