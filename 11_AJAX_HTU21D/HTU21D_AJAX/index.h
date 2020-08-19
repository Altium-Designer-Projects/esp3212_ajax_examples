const char index_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>

<style>
/*
#h1{
  width:500px;
  margin:0 auto;
  margin-top:100px;
  font-size:100px;
  color : rgb(0, 64, 255);
}*/
</style>

<body onload = "ajax_read()">

<h1 id = "temp_rsp">...</h1>
<h1 id = "hum_rsp">...</h1>

 <script>
  function ajax_read(){
    nocache = "&nocache=" + Math.random() * 1000;
    var request = new XMLHttpRequest();
    request.onreadystatechange = function()
    {
      if (this.readyState == 4 && this.status == 200) {
         if (this.responseXML != null) {
            document.getElementById("temp_rsp").innerHTML = this.responseXML.getElementsByTagName("temp")[0].childNodes[0].nodeValue;
            document.getElementById("hum_rsp").innerHTML = this.responseXML.getElementsByTagName("hum")[0].childNodes[0].nodeValue;
         }
      }
    }
    request.open("GET", "request" + nocache, true);
    request.send(null);
    setTimeout('counter()', 1000);
  }
 </script>
</body>
</html>)=====";
