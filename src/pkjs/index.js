Pebble.addEventListener("ready", function(e){
  console.log("Put me in coach!");
});

Pebble.addEventListener("appmessage", function(e){
  console.log("Got Testkey with value " + e.payload);
});