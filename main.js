

var monstro;
$.ajaxSetup({
    async: false
});
     $.getJSON('http://192.168.1.106/cgi-bin/v2/main.cgi?request=2', function (data) {
        monstro = data;
 
      });


var actualhppx =  parseFloat($(".hpfill").css('width'));
var totalhppx =  parseFloat($(".hp").css('width'));
var actualhp = actualhppx/totalhppx;
var totalhp = 100;
//var sprite = monstro.sprite;

$(".death").css({ "background-image":"url('css/monsprite/"+ monstro.sprite +".gif')"});
var lastdamage;

console.log("asdada");
//console.log(monstro.sprite);


function attack(e) {
var damage = Math.floor(Math.random() * monstro.attack) + monstro.attack/2; 
lastdamage = damage; 
actualhp = parseFloat((((monstro.hp*actualhp) - damage)/monstro.hp).toFixed(2));
$(".hpfill").css('width', ''+ (actualhp*100) +'%');

console.log(actualhp);
if(actualhp <= 0)  {

     $.getJSON('http://192.168.1.106/cgi-bin/v2/main.cgi?request=2', function (data) {
        monstro = data;
        console.log("asdasd");
        $(".death").css({ "background-image":"url('css/monsprite/"+ monstro.sprite +".gif')"});

actualhppx = totalhppx;
actualhp = actualhppx/totalhppx;
 
      });

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

    $('.death').prepend("<div class='attackbubble'>"+ lastdamage +"</div>");
setTimeout(function() {
  $('.attackbubble:last').remove();
}, 500);
}	


//--------------------------
divhit = document.getElementById("death");


divhit.addEventListener("click", function(e) {
   attack(e);
  

}, false);



