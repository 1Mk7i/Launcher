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
