var actualhppx = parseFloat($("#enemyhpfill").css('width'));
var totalhppx = parseFloat($("#enemyhp").css('width'));
var actualhp = actualhppx / totalhppx;
var totalhp = 100;

var actualhppxplayer = parseFloat($("#playerhpfill").css('width'));
var totalhppxplayer = parseFloat($("#playerhp").css('width'));



var actualhpplayer = actualhppxplayer / totalhppxplayer;
var totalhpplayer = 100;
var damagemonstro;



var divplayer
var damage = 0;
var neededxp;

var playerid = $('#id').val();
console.log(playerid);
var monstro;

var player;


function updateuser() {


    $.getJSON('index.cgi?request=1&id=' + playerid + '', function(user) {
        player = user;
        $(".gold").html(player.gold);
        $(".statusbar h1").html(player.pontos);
        $(".level").html("Level: " + player.level);
        $("#forvalue").html(player.forca);
        $("#vitvalue").html(player.vitalidade);
        $("#resvalue").html(player.resistencia);


    });

}

function setup() {

    updateuser();
    $.getJSON('index.cgi?request=2&id=' + playerid + '', function(data) {
        monstro = data;
        $(".monstro").css({
            "background-image": "url('../css/monsprite/" + monstro.sprite + ".gif')"
        });



    });


}

function getmonster() {


    $.getJSON('index.cgi?request=2&id=' + playerid + '&xp=' + monstro.xp + '&gold=' + monstro.gold + '', function(monster) {
        monstro = monster;
        $(".monstro").css({
            "background-image": "url('../css/monsprite/" + monstro.sprite + ".gif')"
        });


        console.log(monstro.gold, monstro.xp);
    });

}

function fillenemyhp() {

    actualhppx = totalhppx;
    actualhp = actualhppx / totalhppx;
    $("#enemyhpfill").css('width', '' + (actualhp * 100) + '%');

}


setup();




function attack(e) {


    damage = parseFloat((Math.random() % player.forca) + (player.forca / 1.2)).toFixed(2);
    console.log(damage, player.forca);

    actualhp = parseFloat((((monstro.hp * actualhp) - damage) / monstro.hp).toFixed(2));
    $("#enemyhpfill").css('width', '' + (actualhp * 100) + '%');

    console.log(actualhp);
    if (actualhp <= 0) {
        getmonster();
        fillenemyhp();

        updateuser();
        console.log("-----------------------");
        console.log(monstro.gold, monstro.xp);
        console.log("-----------------------");
    }

    console.log(monstro.sprite);

    e.preventDefault;

    // -> removing the class
    divhit.classList.remove("hit");

    // -> triggering reflow /* The actual magic */
    // without this it wouldn't work. Try uncommenting the line and the transition won't be retriggered.
    divhit.offsetWidth = divhit.offsetWidth;

    // -> and re-adding the class
    divhit.classList.add("hit");

    var el = $(".effect"),
        newone = el.clone(true);

    el.before(newone);

    $(".attack:last").remove();

    $('.monstro').prepend("<div class='attackbubble'>" + damage + "</div>");
    setTimeout(function() {
        $('.attackbubble:last').remove();
    }, 500);
}


//--------------------------
divhit = document.getElementById("monstro");


divhit.addEventListener("click", function(e) {
    attack(e);


}, false);



var ataquemonstro = setInterval(function() {

    damagemonstro = Math.floor(Math.random() * monstro.attack) + monstro.attack / 2;
    damagemonstro = parseFloat(damagemonstro * ((4000 + player.resistencia) / (4000 + player.resistencia * 10))).toFixed(2);

    actualhpplayer = parseFloat((((player.hp * actualhpplayer) - damagemonstro) / player.hp).toFixed(2));
    $("#playerhpfill").css('width', '' + (actualhpplayer * 100) + '%');
    console.log(damagemonstro, actualhpplayer);


    $('.monstro').prepend("<div class='attackbubbleplayer'>" + damagemonstro + "</div>");
    setTimeout(function() {
        $('.attackbubbleplayer:last').remove();
    }, 500);




    divplayer = document.getElementById("fromback");

    // -> removing the class
    divplayer.classList.remove("hit");

    // -> triggering reflow /* The actual magic */
    // without this it wouldn't work. Try uncommenting the line and the transition won't be retriggered.
    divplayer.offsetWidth = divplayer.offsetWidth;

    // -> and re-adding the class
    divplayer.classList.add("hit");


    if (actualhpplayer < 0) {
        clearInterval(ataquemonstro);




        $(".content").empty();
        $(".content").append("<div class='death'><div class='deathicon'></div><h1>Você morreu</h1><div>Perdeu 2 níveis e 10% de cada status</div><a href='index.cgi?request=0&id=" + playerid + "'>Jogar Novamente!</a></div>");

        $.getJSON('index.cgi?request=5&id=' + playerid + '', function() {

        });

        console.log("Você morreu");



    }
}, 1500);


$('.resistencia').bind('click', function() {
    if (gettotalpoints() > 0) {
        var resistencia = parseInt($('#resvalue').html());
        resistencia = resistencia + 1;
        player.resistencia += 1;

        $('#resvalue').before().html(resistencia);



        subtractpoints(1);
    }


});
$('.forca').bind('click', function() {

    if (gettotalpoints() > 0) {
        var forvalue = parseInt($('#forvalue').html());
        forvalue = forvalue + 1;
        player.forca += 1;
 
        $('#forvalue').before().html(forvalue);

        subtractpoints(1);

    }
});
$('.vitalidade').bind('click', function() {

    if (gettotalpoints() > 0) {
        var vitalidade = parseInt($('#vitvalue').html());
        vitalidade = vitalidade + 1;
        player.vitalidade += 1;
        player.hp += 10;
        $('#vitvalue').before().html(vitalidade);

        subtractpoints(1);
    }
});




function subtractpoints(quantidade) {

    var totalpoints = parseInt($('.statusbar h1').text());

    totalpoints -= quantidade;

    $('.statusbar h1').before().html(totalpoints);



}

function gettotalpoints() {

    var totalpoints = parseInt($('.statusbar h1').text());
    return totalpoints;

}


function distribuir() {

    var forvalue = parseInt($('#forvalue').html());
    var resistencia = parseInt($('#resvalue').html());

    var vitalidade = parseInt($('#vitvalue').html());


    $.getJSON('index.cgi?request=4&id=' + playerid + '&for=' + forvalue + '&res=' + resistencia + '&vit=' + vitalidade + '', function() {

    });


 

}

function curar() {

    if (player.gold > player.hp && actualhpplayer < 1) {
        $.getJSON('index.cgi?request=3&id=' + playerid + '', function() {


        });

        actualhppxplayer = totalhppxplayer;
        actualhpplayer = actualhppxplayer / totalhppxplayer;
        $("#playerhpfill").css('width', '' + (actualhpplayer * 100) + '%');
        player.gold -= player.hp;
        $(".gold").html(player.gold);


        


    } else {
        console.log("sem gold");
    }


}