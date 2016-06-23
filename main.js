var actualhppx =  parseFloat($("#enemyhpfill").css('width'));
var totalhppx =  parseFloat($(".hp").css('width'));
var actualhp = actualhppx/totalhppx;
var totalhp = 100;
var damage = 0;

var monstro;
var player = {level:12, hp:100, forca:10, resistencia:12, gold:100};
function getmonster(){

  $.ajaxSetup({
    async: false
});
     $.getJSON('http://192.168.1.23/cgi-bin/main.cgi?request=2', function (data) {
        monstro = data;
          $(".monstro").css({ "background-image":"url('css/monsprite/"+ monstro.sprite +".gif')"});

  
 
      });

}
function fillenemyhp(){

      actualhppx = totalhppx;
          actualhp = actualhppx/totalhppx;
          $("#enemyhpfill").css('width', ''+ (actualhp*100) +'%');

}

getmonster();
console.log(player.level, player.hp);

function updateuser(){
	$(".gold").html(player.gold);

}


function attack(e) {
damage = Math.floor(Math.random() * monstro.attack) + monstro.attack/2; 
lastdamage = damage; 
actualhp = parseFloat((((monstro.hp*actualhp) - damage)/monstro.hp).toFixed(2));
$("#enemyhpfill").css('width', ''+ (actualhp*100) +'%');

console.log(actualhp);
if(actualhp <= 0)  {
fillenemyhp();
getmonster();

updateuser();

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

      var el     = $(".effect"),
        newone = el.clone(true);

    el.before(newone);

    $(".attack:last").remove();

    $('.monstro').prepend("<div class='attackbubble'>"+ lastdamage +"</div>");
setTimeout(function() {
  $('.attackbubble:last').remove();
}, 500);
}	


//--------------------------
divhit = document.getElementById("monstro");


divhit.addEventListener("click", function(e) {
   attack(e);
  

}, false);



