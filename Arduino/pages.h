const char page1[] PROGMEM = 
   "<!DOCTYPE html>\n"
   "<html>\n"
   "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/>\n"
   "<head>\n"
   "\n"
   "<title>ESP-HVAC</title>\n"
   "<style type=\"text/css\">\n"
   "table,input{\n"
   "border-radius: 5px;\n"
   "box-shadow: 2px 2px 12px #000000;\n"
   "background-image: -moz-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -ms-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -o-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -webkit-linear-gradient(top, #efffff, #50a0ff);\n"
   "background-image: linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-clip: padding-box;\n"
   "}\n"
   ".style1 {border-width: 0;}\n"
   ".style2 {text-align: right;}\n"
   ".style5 {\n"
   "border-radius: 5px;\n"
   "box-shadow: 2px 2px 12px #000000;\n"
   "background-image: -moz-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -ms-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -o-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -webkit-linear-gradient(top, #ff0000, #ffa0a0);\n"
   "background-image: linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "}\n"
   "body{width:340px;display:block;font-family: Arial, Helvetica, sans-serif;}\n"
   "</style>\n"
   "\n"
   "<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>\n"
   "\n"
   "<script type=\"text/javascript\">\n"
   "<!--\n"
   "\n"
   "var Json,mode,autoMode,heatMode,fanMode,running,fan,humidMode,ovrActive,away,rh\n"
   "var a=document.all\n"
   "var states = new Array('Idle','Cooling','HP Heat','NG Heat')\n"
   "\n"
   "function startEvents()\n"
   "{\n"
   "ev= new EventSource(\"events?i=30&p=1\")\n"
   "ev.addEventListener('open',function(e){},false)\n"
   "ev.addEventListener('error',function(e){},false)\n"
   "ev.addEventListener('state',function(e){\n"
   "console.log(e)\n"
   "console.log(e.data)\n"
   "Json=JSON.parse(e.data)\n"
   "running= +Json.r\n"
   "fan= +Json.fr\n"
   "rh= +Json.h\n"
   "away=+Json.aw\n"
   "a.intemp.innerHTML= +Json.it/10\n"
   "a.rh.innerHTML= +Json.rh/10\n"
   "a.target.innerHTML= +Json.tt/10\n"
   "a.outtemp.innerHTML= +Json.ot/10\n"
   "a.cyctimer.innerHTML=secsToTime(+Json.ct)\n"
   "a.runtotal.value=secsToTime(+Json.rt)\n"
   "a.filter.value=s2t(+Json.fm)\n"
   "a.fan.innerHTML=fan?\"Fan On\":\"Fan Off\"\n"
   "a.run.innerHTML=states[+Json.s]\n"
   "a.hm.innerHTML=rh?\"Humidifier On\":\"Humidifier Off\"\n"
   "setAtt()\n"
   "},false)\n"
   "ev.addEventListener('alert',function(e){\n"
   "alert(e.data)\n"
   "},false)\n"
   "}\n"
   "\n"
   "function readSettings()\n"
   "{\n"
   "$.getJSON(\"json\", function(Json){\n"
   "     mode= +Json.m\n"
   "  autoMode= +Json.am\n"
   "  heatMode= +Json.hm\n"
   "  fanMode= +Json.fm\n"
   "  humidMode= +Json.rhm\n"
   "  ovrActive= +Json.ot\n"
   "  setAtt()\n"
   "  a.cooll.value= +Json.c0/10\n"
   "  a.coolh.value= +Json.c1/10\n"
   "  a.heatl.value= +Json.h0/10\n"
   "  a.heath.value= +Json.h1/10\n"
   "  a.ovrtime.value= s2t(+Json.ov)\n"
   "  a.fantime.value= s2t(+Json.fct)\n"
   "  a.awaytemp.value= +Json.ad/10\n"
   " if( +a.ovrtemp.value==0)\n"
   "  a.ovrtemp.value= -2.0\n"
   "});\n"
   "}\n"
   "\n"
   "function setVar(varName, value)\n"
   "{\n"
   "$.get('s?key='+a.myToken.value+'&'+varName+'='+value)\n"
   "}\n"
   "\n"
   "function setfan(n)\n"
   "{\n"
   "if(n<3) fanMode=n\n"
   "setVar('fanmode',n)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function setMode(m)\n"
   "{\n"
   "setVar('mode',mode=m)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function setHeatMode(m)\n"
   "{\n"
   "setVar('heatmode',heatMode=m)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function setHumidMode(m)\n"
   "{\n"
   "setVar('humidmode',humidMode=m)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function setAway()\n"
   "{\n"
   "away=!away\n"
   "setVar('away',away?1:0)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function rstFlt()\n"
   "{\n"
   "setVar('resetfilter',0)\n"
   "}\n"
   "\n"
   "function rstTot()\n"
   "{\n"
   "setVar('resettotal',0)\n"
   "}\n"
   "\n"
   "function setAtt()\n"
   "{\n"
   "a.runCell.setAttribute('class',running?'style5':'style1')\n"
   "a.hmCell.setAttribute('class',rh?'style5':'style1')\n"
   "a.fAuto.setAttribute('class',fanMode==0?'style5':'')\n"
   "a.fOn.setAttribute('class',fanMode==1?'style5':'')\n"
   "a.fS.setAttribute('class',fanMode==2?'style5':'')\n"
   "a.fan.innerHTML = \"Fan \"+((fanMode==1)?\"On\":(fan?\"On\":\"Off\"))\n"
   "a.fanCell.setAttribute('class',fan?'style5' : 'style1')\n"
   "a.ovrCell.setAttribute('class',away?'style1':(ovrActive?'style5':'style1'))\n"
   "\n"
   "a.mOff.setAttribute('class',mode==0?'style5':'')\n"
   "a.mCool.setAttribute('class',mode==1?'style5':'')\n"
   "a.mHeat.setAttribute('class',mode==2?'style5':'')\n"
   "a.mAuto.setAttribute('class',mode==3?'style5':'')\n"
   "\n"
   "a.hHP.setAttribute('class',heatMode==0?'style5':'')\n"
   "a.hGas.setAttribute('class',heatMode==1?'style5':'')\n"
   "a.hAuto.setAttribute('class',heatMode==2?'style5':'')\n"
   "\n"
   "a.hmOff.setAttribute('class',humidMode==0?'style5':'')\n"
   "a.hmFan.setAttribute('class',humidMode==1?'style5':'')\n"
   "a.hmRun.setAttribute('class',humidMode==2?'style5':'')\n"
   "a.hmAuto1.setAttribute('class',humidMode==3?'style5':'')\n"
   "a.hmAuto2.setAttribute('class',humidMode==4?'style5':'')\n"
   "a.away.setAttribute('class',away?'style5':'')\n"
   "}\n"
   "\n"
   "function setCoolHi()\n"
   "{\n"
   "setVar('cooltemph',(+a.coolh.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setCoolLo()\n"
   "{\n"
   "setVar('cooltempl',(+a.cooll.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function incCool(n)\n"
   "{\n"
   "a.coolh.value= +a.coolh.value+n\n"
   "a.cooll.value= +a.cooll.value+n\n"
   "\n"
   "setVar('cooltemph',(+a.coolh.value*10).toFixed())\n"
   "setVar('cooltempl',(+a.cooll.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setHeatHi()\n"
   "{\n"
   "setVar('heattemph',(+a.heath.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setHeatLo()\n"
   "{\n"
   "setVar('heattempl',(+a.heatl.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function incHeat(n)\n"
   "{\n"
   "a.heath.value= +a.heath.value+n\n"
   "a.heatl.value= +a.heatl.value+n\n"
   "\n"
   "setVar('heattemph',(+a.heath.value*10).toFixed())\n"
   "setVar('heattempl',(+a.heatl.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setOvrTime()\n"
   "{\n"
   "  setVar('overridetime',t2s(a.ovrtime.value))\n"
   "}\n"
   "\n"
   "function setOvrTemp()\n"
   "{\n"
   "  setVar('override',(+a.ovrtemp.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function cancelOvr()\n"
   "{\n"
   "  setVar('override',0)\n"
   "}\n"
   "\n"
   "function setFanTime()\n"
   "{\n"
   "  setVar('fantime',t2s(a.fantime.value))\n"
   "}\n"
   "\n"
   "function setAwayTemp()\n"
   "{\n"
   "  setVar('awaydelta',(+a.awaytemp.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function secsToTime( elap )\n"
   "{\n"
   "  d=0\n"
   "  m=0\n"
   "  h=Math.floor(elap/3600)\n"
   "  if(h >23)\n"
   "  {\n"
   "    d=Math.floor(h/24)\n"
   "    h-=(d*24)\n"
   "  }\n"
   "  else\n"
   "  {\n"
   "    m=Math.floor((elap-(h*3600))/60)\n"
   "    s=elap-(h*3600)-(m*60)\n"
   "    if(s<10) s='0'+s\n"
   "    if(h==0)\n"
   "    {\n"
   "      if( m < 10) m='  '+m\n"
   "      return '    '+m +':'+s\n"
   "    }\n"
   "  }\n"
   "  if(m<10) m='0'+m\n"
   "  if(h<10) h='  '+h\n"
   "  if(d) return d+'d '+h+'h'\n"
   "  return h+':'+m+':'+s\n"
   "}\n"
   "\n"
   "function s2t(elap)\n"
   "{\n"
   "  m=Math.floor(elap/60)\n"
   "  s=elap-(m*60)\n"
   "  if(m==0) return s\n"
   "  if(s<10) s='0'+s\n"
   "  return m+':'+s\n"
   "}\n"
   "\n"
   "function t2s(v)\n"
   "{\n"
   "  if(typeof v == 'string') v = (+v.substr(0, v.indexOf(':'))*60) + (+v.substr(v.indexOf(':')+1))\n"
   "  return v\n"
   "}\n"
   "//--></script>\n"
   "</head>\n"
   "<body onload=\"{\n"
   " myStorage1 = localStorage.getItem('myStoredText1')\n"
   " if(myStorage1  != null){\n"
   "  a.myToken.style.visibility = 'hidden'\n"
   "  a.hide.value='Show'\n"
   "  document.getElementById('myToken').value=myStorage1\n"
   " }\n"
   " readSettings()\n"
   "  \n"
   " myStorage3 = localStorage.getItem('myStoredText3')\n"
   " if(myStorage3  != null){\n"
   "  document.getElementById('ovrtemp').value=myStorage3\n"
   " }\n"
   " startEvents()\n"
   "}\">\n"
   "<strong><em>CuriousTech HVAC Remote</em></strong><br>\n"
   "<font size=4>\n"
   "<p><table style=\"width: 350px; height: 22px;\" cellspacing=\"0\">\n"
   "<tr>\n"
   "<td>In</td><td><div id=\"intemp\" class=\"style2\">in</div></td><td>&deg</td><td> &gt;</td>\n"
   "<td><div id=\"target\" class=\"style2\">trg</div></td><td>&deg</td>\n"
   "<td><div id=\"rh\" class=\"style2\">rh</div></td><td>%</td>\n"
   "<td>Out</td><td><div id=\"outtemp\" class=\"style2\">out</div></td><td>&deg</td>\n"
   "</tr>\n"
   "</table>\n"
   "</font></p>\n"
   "<table style=\"width: 350px\" cellspacing=\"0\" cellpadding=\"0\">\n"
   "<tr>\n"
   "<td id=\"fanCell\"><div id=\"fan\">Fan Off</div></td>\n"
   "<td align=\"right\"><input type=\"button\" value=\"Auto\" name=\"fAuto\" onClick=\"{setfan(0)}\"></td>\n"
   "<td width=\"40\"><input type=\"button\" value=\" On \" name=\"fOn\" onClick=\"{setfan(1)}\"><input type=\"button\" value=\"Cycl\" name=\"fS\" onClick=\"{setfan(2)}\"></td>\n"
   "<td width=300 align=\"right\"><input type=\"submit\" value=\"Settings\" onClick=\"window.location='/settings';\"></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td id=\"runCell\"><div id=\"run\">Cooling</div></td>\n"
   "<td align=\"right\"><input type=\"button\" value=\" Off \" name=\"mOff\" onClick=\"{setMode(0)}\"></td>\n"
   "<td><input type=\"button\" value=\"Cool\" name=\"mCool\" onClick=\"{setMode(1)}\"><input type=\"button\" value=\"Heat\" name=\"mHeat\" onClick=\"{setMode(2)}\"></td>\n"
   "<td>\n"
   "<input type=\"button\" value=\"Auto\" name=\"mAuto\" onClick=\"{setMode(3)}\">"
   "&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<input type=\"submit\" value=\"Chart\" onClick=\"window.location='/chart.html';\">"
   "</td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>&nbsp</td>\n"
   "<td></td>\n"
   "<td></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Cool Hi</td>\n"
   "<td><input type=text size=3 id=\"coolh\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setCoolHi()}\"><input type=\"button\" value=\"+1\" onClick=\"{incCool(1)}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td style=\"width: 81px\">Cool Lo</td>\n"
   "<td style=\"width: 44px\"><input type=text size=3 id=\"cooll\"></td>\n"
   "<td style=\"width: 200px\"><input type=\"button\" value=\"Set\" onClick=\"{setCoolLo()}\"><input type=\"button\" value=\" -1\" onClick=\"{incCool(-1)}\"></td>\n"
   "<td><input type=\"button\" value=\" HP \" name=\"hHP\" onClick=\"{setHeatMode(0)}\"><input type=\"button\" value=\"Gas \" name=\"hGas\" onClick=\"{setHeatMode(1)}\"><input type=\"button\" value=\"Auto\" name=\"hAuto\" onClick=\"{setHeatMode(2)}\"></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Heat Hi</td>\n"
   "<td><input type=text size=3 id=\"heath\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setHeatHi()}\"><input type=\"button\" value=\"+1\" onClick=\"{incHeat(1)}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Heat Lo</td>\n"
   "<td><input type=text size=3 id=\"heatl\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setHeatLo()}\"><input type=\"button\" value=\" -1\" onClick=\"{incHeat(-1)}\"></td>\n"
   "<td id=\"hmCell\"><div id=\"hm\">Humidifier Off</div></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td></td>\n"
   "<td></td>\n"
   "<td></td>\n"
   "<td>\n"
   "<input type=\"button\" value=\" Off \" name=\"hmOff\" onClick=\"{setHumidMode(0)}\"><input type=\"button\" value=\"Fan\" name=\"hmFan\" onClick=\"{setHumidMode(1)}\"></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>ovr Time</td>\n"
   "<td><input type=text size=3 id=\"ovrtime\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setOvrTime()}\"></td>\n"
   "<td>\n"
   "<input type=\"button\" value=\"Run\" name=\"hmRun\" onClick=\"{setHumidMode(2)}\"></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td id=\"ovrCell\">Overrd &Delta;</td>\n"
   "<td><input type=text size=3 id=\"ovrtemp\"></td>\n"
   "<td><input type=\"button\" value=\"Go \" onClick=\"{localStorage.setItem('myStoredText3', a.ovrtemp.value);setOvrTemp()}\"><input type=\"button\" value=\"Stop\" onClick=\"{cancelOvr()}\">\n"
   "</td>\n"
   "<td>\n"
   "<input type=\"button\" value=\" A1 \" name=\"hmAuto1\" onClick=\"{setHumidMode(3)}\"><input type=\"button\" value=\" A2 \" name=\"hmAuto2\" onClick=\"{setHumidMode(4)}\"></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Freshen</td>\n"
   "<td><input type=text size=3 id=\"fantime\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setFanTime()}\"><input type=\"button\" value=\" Go  \" onClick=\"{setfan(3)}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Away &Delta;</td>\n"
   "<td><input type=text size=3 id=\"awaytemp\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setAwayTemp()}\"></td>\n"
   "<td><input type=\"button\" value=\"Away\" name=\"away\" onClick=\"{setAway()}\"></td>\n"
   "</tr>\n"
   "</table><br/>\n"
   "<table style=\"width: 350px\">\n"
   "<tr>\n"
   "<td>Cycle</td><td><div id=\"cyctimer\" style=\"width: 70px\">0</div></td>\n"
   "<td>Total</td><td><input type=\"button\" id =\"runtotal\" value=\"0\" onClick=\"{rstTot()}\"></td>\n"
   "<td>Filter</td><td><input type=\"button\" id =\"filter\" value=\"0\" onClick=\"{rstFlt()}\"></td>\n"
   "</tr>\n"
   "</table>\n"
   "<p>\n"
   "<table style=\"width: 350px\">\n"
   "<tr>\n"
   "<td>Password</td>\n"
   "<td>\n"
   "<input id=\"myToken\" name=\"access_token\" type=text size=40 placeholder=\"e6bba7456a7c9\" style=\"width: 150px\">\n"
   "</td><td>\n"
   "<input type=\"button\" value=\"Save\" onClick=\"{\n"
   " localStorage.setItem('myStoredText1', a.myToken.value)\n"
   " alert(a.myToken.value+' Has been stored')\n"
   "}\">\n"
   "<input type=\"button\" value=\"Hide\" name=\"hide\" onClick=\"{\n"
   "if(a.myToken.style.visibility == 'hidden'){\n"
   " a.myToken.style.visibility = 'visible'\n"
   " a.hide.value='Hide'\n"
   " }else{\n"
   " a.myToken.style.visibility = 'hidden'\n"
   " a.hide.value='Show'\n"
   "}\n"
   "}\">\n"
   "</td>\n"
   "</tr>\n"
   "</table></p>\n"
   "<small>Copyright &copy 2016 CuriousTech.net</small>\n"
   "</body>\n"
   "</html>\n";

const char page2[] PROGMEM = 
   "<!DOCTYPE html>\n"
   "<html>\n"
   "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/>\n"
   "<head>\n"
   "\n"
   "<title>ESP-HVAC</title>\n"
   "<style type=\"text/css\">\n"
   "table,input{\n"
   "border-radius: 5px;\n"
   "box-shadow: 2px 2px 12px #000000;\n"
   "background-image: -moz-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -ms-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -o-linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-image: -webkit-linear-gradient(top, #efffff, #50a0ff);\n"
   "background-image: linear-gradient(top, #ffffff, #50a0ff);\n"
   "background-clip: padding-box;\n"
   "}\n"
   ".style1 {border-width: 0;}\n"
   ".style2 {text-align: right;}\n"
   ".style5 {\n"
   "border-radius: 5px;\n"
   "box-shadow: 2px 2px 12px #000000;\n"
   "background-image: -moz-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -ms-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -o-linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "background-image: -webkit-linear-gradient(top, #ff0000, #ffa0a0);\n"
   "background-image: linear-gradient(top, #ff00ff, #ffa0ff);\n"
   "}\n"
   "body{width:340px;display:block;font-family: Arial, Helvetica, sans-serif;}\n"
   "</style>\n"
   "\n"
   "<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>\n"
   "\n"
   "<script type=\"text/javascript\">\n"
   "<!--\n"
   "\n"
   "var Json,ovrActive,away,rmtMode\n"
   "var a=document.all\n"
   "var states = new Array('Idle','Cooling','HP Heat','NG Heat')\n"
   "\n"
   "function startEvents()\n"
   "{\n"
   "ev= new EventSource(\"events?i=30&p=1\")\n"
   "ev.addEventListener('open',function(e){},false)\n"
   "ev.addEventListener('error',function(e){},false)\n"
   "ev.addEventListener('state',function(e){\n"
   "console.log(e)\n"
   "console.log(e.data)\n"
   "Json=JSON.parse(e.data)\n"
   "away=+Json.aw\n"
   "setAtt()\n"
   "},false)\n"
   "ev.addEventListener('alert',function(e){\n"
   "alert(e.data)\n"
   "},false)\n"
   "}\n"
   "\n"
   "function readSettings()\n"
   "{\n"
   "$.getJSON(\"json\", function(Json){\n"
   "  setAtt()\n"
   "  a.humidl.value= +Json.rh0/10\n"
   "  a.humidh.value= +Json.rh1/10\n"
   "  a.idlemin.value= s2t(+Json.im)\n"
   "  a.cycmin.value= s2t(+Json.cn)\n"
   "  a.cycmax.value= s2t(+Json.cx)\n"
   "  a.thresh.value= +Json.ct/10\n"
   "  a.fandelay.value= s2t(+Json.fd)\n"
   "  a.fanpre.value= s2t(+Json.fp)\n"
   "  a.awaytime.value= s2t(+Json.at)\n"
   "  a.heatthr.value= +Json.ht\n"
   "  rmtMode=+Json.ar\n"
   "});\n"
   "}\n"
   "\n"
   "function setVar(varName, value)\n"
   "{\n"
   "$.get('s?key='+a.myToken.value+'&'+varName+'='+value)\n"
   "}\n"
   "\n"
   "function setAway()\n"
   "{\n"
   "away=!away\n"
   "setVar('away',away?1:0)\n"
   "setAtt()\n"
   "}\n"
   "\n"
   "function setAtt()\n"
   "{\n"
   "a.rmth1.setAttribute('class',(rmtMode&10)==8?'style5':'')\n"
   "a.rmth2.setAttribute('class',(rmtMode&10)==10?'style5':'')\n"
   "a.rmth3.setAttribute('class',(rmtMode&10)==2?'style5':'')\n"
   "a.rmtl1.setAttribute('class',(rmtMode&5)==4?'style5':'')\n"
   "a.rmtl2.setAttribute('class',(rmtMode&5)==5?'style5':'')\n"
   "a.rmtl3.setAttribute('class',(rmtMode&5)==1?'style5':'')\n"
   "}\n"
   "\n"
   "function setHT()\n"
   "{\n"
   "setVar('eheatthresh',+a.heatthr.value)\n"
   "}\n"
   "\n"
   "function setHumidHi()\n"
   "{\n"
   "setVar('humidh',(+a.humidh.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setHumidLo()\n"
   "{\n"
   "setVar('humidl',(+a.humidl.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function incHumid(n)\n"
   "{\n"
   "a.humidh.value= +a.humidh.value+n\n"
   "a.humidl.value= +a.humidl.value+n\n"
   "\n"
   "setVar('humidh',(+a.humidh.value*10).toFixed())\n"
   "setVar('humidl',(+a.humidl.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setThresh()\n"
   "{\n"
   "setVar('cyclethresh',(+a.thresh.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setFanDelay()\n"
   "{\n"
   "setVar('fanpostdelay',t2s(a.fandelay.value))\n"
   "}\n"
   "\n"
   "function setFanPre()\n"
   "{\n"
   "setVar('fanpretime',t2s(a.fanpre.value))\n"
   "}\n"
   "\n"
   "function setIdleMin()\n"
   "{\n"
   "setVar('idlemin',t2s(a.idlemin.value))\n"
   "}\n"
   "\n"
   "function setCycMin()\n"
   "{\n"
   "setVar('cyclemin',t2s(a.cycmin.value))\n"
   "}\n"
   "\n"
   "function setCycMax()\n"
   "{\n"
   "setVar('cyclemax',t2s(a.cycmax.value))\n"
   "}\n"
   "\n"
   "function setOvrTime()\n"
   "{\n"
   "  setVar('overridetime',t2s(a.ovrtime.value))\n"
   "}\n"
   "\n"
   "function setOvrTemp()\n"
   "{\n"
   "  setVar('override',(+a.ovrtemp.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function cancelOvr()\n"
   "{\n"
   "  setVar('override',0)\n"
   "}\n"
   "\n"
   "function setFanTime()\n"
   "{\n"
   "  setVar('fantime',t2s(a.fantime.value))\n"
   "}\n"
   "\n"
   "function setAwayTime()\n"
   "{\n"
   "  setVar('awaytime',t2s(a.awaytime.value))\n"
   "}\n"
   "\n"
   "function setAwayTemp()\n"
   "{\n"
   "  setVar('awaydelta',(+a.awaytemp.value*10).toFixed())\n"
   "}\n"
   "\n"
   "function setRmt(v)\n"
   "{\n"
   "  switch(v)\n"
   "  {\n"
   "    case 1: rmtMode&=0xFD;rmtMode|=8;break;\n"
   "    case 2: rmtMode|=10;break;\n"
   "    case 3: rmtMode&=0xF7;rmtMode|=2;break;\n"
   "    case 4: rmtMode&=0xFE;rmtMode|=4;break;\n"
   "    case 5: rmtMode|=5;break;\n"
   "    case 6: rmtMode&=0xFB;rmtMode|=1;break;\n"
   "  }\n"
   "  setVar('rmtflgs',rmtMode)\n"
   "  setAtt()\n"
   "}\n"
   "\n"
   "function secsToTime( elap )\n"
   "{\n"
   "  d=0\n"
   "  m=0\n"
   "  h=Math.floor(elap/3600)\n"
   "  if(h >23)\n"
   "  {\n"
   "    d=Math.floor(h/24)\n"
   "    h-=(d*24)\n"
   "  }\n"
   "  else\n"
   "  {\n"
   "    m=Math.floor((elap-(h*3600))/60)\n"
   "    s=elap-(h*3600)-(m*60)\n"
   "    if(s<10) s='0'+s\n"
   "    if(h==0)\n"
   "    {\n"
   "      if( m < 10) m='  '+m\n"
   "      return '    '+m +':'+s\n"
   "    }\n"
   "  }\n"
   "  if(m<10) m='0'+m\n"
   "  if(h<10) h='  '+h\n"
   "  if(d) return d+'d '+h+'h'\n"
   "  return h+':'+m+':'+s\n"
   "}\n"
   "\n"
   "function s2t(elap)\n"
   "{\n"
   "  m=Math.floor(elap/60)\n"
   "  s=elap-(m*60)\n"
   "  if(m==0) return s\n"
   "  if(s<10) s='0'+s\n"
   "  return m+':'+s\n"
   "}\n"
   "\n"
   "function t2s(v)\n"
   "{\n"
   "  if(typeof v == 'string') v = (+v.substr(0, v.indexOf(':'))*60) + (+v.substr(v.indexOf(':')+1))\n"
   "  return v\n"
   "}\n"
   "//--></script>\n"
   "</head>\n"
   "<body onload=\"{\n"
   " myStorage1 = localStorage.getItem('myStoredText1')\n"
   " if(myStorage1  != null){\n"
   "  a.myToken.style.visibility = 'hidden'\n"
   "  a.hide.value='Show'\n"
   "  document.getElementById('myToken').value=myStorage1\n"
   " }\n"
   " readSettings()\n"
   "  \n"
   " myStorage3 = localStorage.getItem('myStoredText3')\n"
   " if(myStorage3  != null){\n"
   "  document.getElementById('ovrtemp').value=myStorage3\n"
   " }\n"
   " startEvents()\n"
   "}\">\n"
   "<strong><em>CuriousTech HVAC Remot Settings</em></strong><br><br>\n"
   "<table style=\"width: 350px\" cellspacing=\"0\" cellpadding=\"0\">\n"
   "<tr>\n"
   "<td style=\"width: 81px\">Threshold</td>\n"
   "<td style=\"width: 44px\"><input type=text size=4 id=\"thresh\"></td>\n"
   "<td style=\"width: 140px\"><input type=\"button\" value=\"Set\" onClick=\"{setThresh()}\"></td>\n"
   "<td>\n"
   "<input type=\"submit\" value=\"Main\" onClick=\"window.location='/';\">\n"
   "</td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Heat Thr</td>\n"
   "<td><input type=text size=4 id=\"heatthr\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setHT()}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Humid Hi</td>\n"
   "<td><input type=text size=4 id=\"humidh\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setHumidHi()}\"><input type=\"button\" value=\"+1\" onClick=\"{incHumid(1)}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Humid Lo</td>\n"
   "<td><input type=text size=4 id=\"humidl\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setHumidLo()}\"><input type=\"button\" value=\" -1\" onClick=\"{incHumid(-1)}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Pre Fan</td>\n"
   "<td><input type=text size=4 id=\"fanpre\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setFanPre()}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Post Fan</td>\n"
   "<td><input type=text size=4 id=\"fandelay\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setFanDelay()}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Idle Min</td>\n"
   "<td><input type=text size=4 id=\"idlemin\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setIdleMin()}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>cycle Min</td>\n"
   "<td><input type=text size=4 id=\"cycmin\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setCycMin()}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>cycle Max</td>\n"
   "<td><input type=text size=4 id=\"cycmax\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setCycMax()}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Away Lmt</td>\n"
   "<td><input type=text size=4 id=\"awaytime\"></td>\n"
   "<td><input type=\"button\" value=\"Set\" onClick=\"{setAwayTime()}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td></td>\n"
   "<td></td>\n"
   "<td></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Remote Hi</td>\n"
   "<td><input type=\"button\" value=\"Remote\" name=\"rmth1\" onClick=\"{setRmt(1)}\"></td>\n"
   "<td><input type=\"button\" value=\"Avg\" name=\"rmth2\" onClick=\"{setRmt(2)}\"><input type=\"button\" value=\"Main\" name=\"rmth3\" onClick=\"{setRmt(3)}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "<tr>\n"
   "<td>Remote Lo</td>\n"
   "<td><input type=\"button\" value=\"Remote\" name=\"rmtl1\" onClick=\"{setRmt(4)}\"></td>\n"
   "<td><input type=\"button\" value=\"Avg\" name=\"rmtl2\" onClick=\"{setRmt(5)}\"><input type=\"button\" value=\"Main\" name=\"rmtl3\" onClick=\"{setRmt(6)}\"></td>\n"
   "<td></td>\n"
   "</tr>\n"
   "</table>\n"
   "<p>\n"
   "<table style=\"width: 350px\">\n"
   "<tr>\n"
   "<td>Password</td>\n"
   "<td>\n"
   "<input id=\"myToken\" name=\"access_token\" type=text size=40 placeholder=\"e6bba7456a7c9\" style=\"width: 150px\">\n"
   "<input type=\"button\" value=\"Save\" onClick=\"{\n"
   " localStorage.setItem('myStoredText1', a.myToken.value)\n"
   " alert(a.myToken.value+' Has been stored')\n"
   "}\">\n"
   "<input type=\"button\" value=\"Hide\" name=\"hide\" onClick=\"{\n"
   "if(a.myToken.style.visibility == 'hidden'){\n"
   " a.myToken.style.visibility = 'visible'\n"
   " a.hide.value='Hide'\n"
   " }else{\n"
   " a.myToken.style.visibility = 'hidden'\n"
   " a.hide.value='Show'\n"
   "}\n"
   "}\">\n"
   "</td>\n"
   "</tr>\n"
   "</table></p>\n"
   "<small>Copyright &copy 2016 CuriousTech.net</small>\n"
   "</body>\n"
   "</html>\n";

const char chart1[] PROGMEM = 
   "<!DOCTYPE html>\n"
   "<html>\n"
   "<head>\n"
   "<title>HVAC Chart</title>\n"
   "<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>\n"
   "<script>\n"
   "\n"
   "var graph;\n"
   "var xPadding = 30\n"
   "var yPadding = 100\n"
   "var yRange\n"
   "var timeInc = 1000*300\n"
   "var data = { values:[\n";
const char chart2[] PROGMEM = 
   "]};\n"
   "\n"
   "$(document).ready(function() {\n"
   "  graph = $('#graph')\n"
   "  var c = graph[0].getContext('2d')\n"
   "\n"
   "  var tipCanvas = document.getElementById(\"tip\")\n"
   "    var tipCtx = tipCanvas.getContext(\"2d\")\n"
   "  var tipDiv = document.getElementById(\"popup\")\n"
   "\n"
   "    var canvasOffset = graph.offset()\n"
   "    var offsetX = canvasOffset.left\n"
   "    var offsetY = canvasOffset.top\n"
   "\n"
   "  c.lineWidth = 2\n"
   "  c.font = 'italic 8pt sans-serif'\n"
   "  c.textAlign = \"left\"\n"
   "\n"
   "  c.beginPath() // borders\n"
   "  c.moveTo(xPadding, 0)\n"
   "  c.lineTo(xPadding, graph.height()-yPadding)\n"
   "  c.lineTo(graph.width()-xPadding, graph.height()-yPadding)\n"
   "  c.lineTo(graph.width()-xPadding, 0)\n"
   "  c.stroke()\n"
   "\n"
   "  c.lineWidth = 1\n"
   "  // dates\n"
   "  date = new Date((new Date()).valueOf() - (timeInc*(data.values.length-1)))\n"
   "  step = Math.floor(data.values.length / 15)\n"
   "  if(step == 0) step = 1\n"
   "  for(var i = 0; i < data.values.length; i += step) {\n"
   "    if( data.values[i].temp != 'nan')\n"
   "    {\n"
   "      c.save()\n"
   "      c.translate(getXPixel(i), graph.height() - yPadding + 5)\n"
   "      c.rotate(0.9)\n"
   "      c.fillText(date.toLocaleTimeString(), 0, 0)\n"
   "      c.restore()\n"
   "      date = new Date(date.valueOf()+(timeInc*step))\n"
   "    }\n"
   "  }\n"
   "\n"
   "  yRange = (getMaxY() - getMinY()).toFixed()\n"
   "  // value range\n"
   "  c.textAlign = \"right\"\n"
   "  c.textBaseline = \"middle\"\n"
   "\n"
   "  for(var i = getMinY(); i < getMaxY(); i += (yRange / 8) ) {\n"
   "    c.fillText(i.toFixed(1), xPadding - 6, getYPixel(i))\n"
   "  }\n"
   "\n"
   "  c.fillText('Temp', xPadding-4, 4 )\n"
   "  c.fillStyle = \"green\"\n"
   "  c.fillText('Rh', graph.width()-14, 4 )\n"
   "\n"
   "  // rh scale\n"
   "  for(var i = 0; i < 10; i +=2 ) {\n"
   "    pos = graph.height()-8-( ((graph.height()-yPadding) / 10) * i )-yPadding\n"
   "    c.fillText(i*10, graph.width() - 14, pos )\n"
   "  }\n"
   "\n"
   "  // temp lines\n"
   "  for(var i = 0; i < data.values.length-1; i ++) {\n"
   "    if( data.values[i].temp != 'nan')\n"
   "    {\n"
   "      c.fillStyle = c.strokeStyle = stateColor(data.values[i].s)\n"
   "      c.beginPath()\n"
   "      c.moveTo(getXPixel(i), getYPixel(data.values[i].temp))\n"
   "      c.lineTo(getXPixel(i+1), getYPixel(data.values[i+1].temp))\n"
   "      c.stroke()\n"
   "      c.beginPath()\n"
   "        c.arc(getXPixel(i), getYPixel(data.values[i].temp), 2, 0, Math.PI * 2, true);\n"
   "        c.fill();\n"
   "    }\n"
   "  }\n"
   "\n"
   "  // rh lines\n"
   "  c.strokeStyle = '#0f0'\n"
   "  c.beginPath()\n"
   "  c.moveTo(getXPixel(0), getRHPixel(data.values[0].rh))\n"
   "\n"
   "  for(var i = 1; i < data.values.length; i ++) {\n"
   "    if( data.values[i].rh != 'nan')\n"
   "      c.lineTo(getXPixel(i), getRHPixel(data.values[i].rh))\n"
   "  }\n"
   "  c.stroke()\n"
   "\n"
   "  c.strokeStyle = '#cc6'\n"
   "  c.beginPath()\n"
   "  c.moveTo(getXPixel(0), getYPixel(data.values[0].h))\n"
   "\n"
   "  for(var i = 1; i < data.values.length; i ++) {\n"
   "    if( data.values[i].h != 'nan')\n"
   "      c.lineTo(getXPixel(i), getYPixel(data.values[i].h))\n"
   "  }\n"
   "  c.stroke()\n"
   "\n"
   "  c.beginPath()\n"
   "  c.moveTo(getXPixel(0), getYPixel(data.values[0].l))\n"
   "\n"
   "  for(var i = 1; i < data.values.length; i ++) {\n"
   "    if( data.values[i].l != 'nan')\n"
   "      c.lineTo(getXPixel(i), getYPixel(data.values[i].l))\n"
   "  }\n"
   "  c.stroke()\n"
   "\n"
   "  var dots = []\n"
   "    for(var i = 0; i < data.values.length; i ++) {\n"
   "        dots.push({\n"
   "            x: getXPixel(i),\n"
   "            y: getYPixel(data.values[i].temp),\n"
   "            r: 4,\n"
   "            rXr: 16,\n"
   "            color: \"red\",\n"
   "            tip: data.values[i].temp,\n"
   "            tip2: data.values[i].rh,\n"
   "            tip3: 0\n"
   "        })\n"
   "    }\n"
   "\n"
   "    // request mousemove events\n"
   "    graph.mousemove(function(e){handleMouseMove(e);})\n"
   "\n"
   "    // show tooltip when mouse hovers over dot\n"
   "    function handleMouseMove(e){\n"
   "      mouseX=parseInt(e.clientX-offsetX)\n"
   "      mouseY=parseInt(e.clientY-offsetY)\n"
   "\n"
   "      // Put your mousemove stuff here\n"
   "      var hit = false\n"
   "      for (var i = 0; i < dots.length; i++) {\n"
   "          var dot = dots[i]\n"
   "          var dx = mouseX - dot.x\n"
   "          var dy = mouseY - dot.y\n"
   "          if (dx * dx + dy * dy < dot.rXr) {\n"
   "      tipCtx.fillStyle = \"#C0C0C0\"\n"
   "      tipCtx.fillRect(0, 0, tipCanvas.width, tipCanvas.height)\n"
   "\n"
   "      tipCtx.lineWidth = 2\n"
   "      tipCtx.fillStyle = \"#000000\"\n"
   "      tipCtx.strokeStyle = '#333'\n"
   "      tipCtx.font = 'italic 8pt sans-serif'\n"
   "      tipCtx.textAlign = \"left\"\n"
   "    \n"
   "      tipCtx.beginPath() // borders\n"
   "      tipCtx.moveTo(0,0)\n"
   "      tipCtx.lineTo(0,40)\n"
   "      tipCtx.lineTo(60,40)\n"
   "      tipCtx.lineTo(60,0)\n"
   "      tipCtx.lineTo(0,0)\n"
   "      tipCtx.stroke()\n"
   "\n"
   "      tipCtx.fillText( dot.tip + '°F', 5, 15)\n"
   "      tipCtx.fillText( dot.tip2 + '%', 5, 29)\n"
   "      hit = true\n"
   "      popup = document.getElementById(\"popup\")\n"
   "      popup.style.top = dot.y + \"px\"\n"
   "      popup.style.left = (dot.x-90) + \"px\"\n"
   "          }\n"
   "      }\n"
   "      if (!hit) { popup.style.left = \"-200px\" }\n"
   "    }\n"
   "});\n"
   "\n"
   "function getMaxY() {\n"
   "  var max = 0\n"
   "\n"
   "  for(var i = 0; i < data.values.length; i ++)\n"
   "  {\n"
   "    if(data.values[i].temp != 'nan' && data.values[i].temp > max)\n"
   "      max = data.values[i].temp\n"
   "    if(data.values[i].h != 'nan' && data.values[i].h > max)\n"
   "      max = data.values[i].h\n"
   "  }\n"
   "  return Math.floor(max) + 1\n"
   "}\n"
   "\n"
   "function getMinY() {\n"
   "  var min = 200\n"
   "\n"
   "  for(var i = 0; i < data.values.length; i ++)\n"
   "  {\n"
   "    if(data.values[i].temp != 'nan' && data.values[i].temp < min)\n"
   "      min = data.values[i].temp\n"
   "    if(data.values[i].l != 'nan' && data.values[i].l < min)\n"
   "      min = data.values[i].l\n"
   "  }\n"
   "  return Math.floor(min)\n"
   "}\n"
   " \n"
   "function getXPixel(val) {\n"
   "  return ((graph.width()-26-xPadding) / data.values.length) * val + xPadding\n"
   "}\n"
   "\n"
   "function getYPixel(val) {\n"
   "  return graph.height()-6-( ((graph.height() - yPadding) / yRange) * ( val-getMinY() )) - yPadding\n"
   "}\n"
   "\n"
   "function getRHPixel(val) {\n"
   "  return graph.height() - (((graph.height() - yPadding) / 100) * val) - yPadding\n"
   "}\n"
   "\n"
   "function stateColor(s)\n"
   "{\n"
   "  sts=Array('gray','blue','red','red')\n"
   "  return sts[s]\n"
   "}\n"
   "\n"
   "</script>\n"
   "<style type=\"text/css\">\n"
   "#wrapper {\n"
   "  width: 800px;\n"
   "  height: 400px;\n"
   "  position: relative;\n"
   "}\n"
   "#graph {\n"
   "  width: 100%;\n"
   "  height: 100%;\n"
   "  position: absolute;\n"
   "  top: 0;\n"
   "  left: 0;\n"
   "}\n"
   "#popup {\n"
   "  width: 60;\n"
   "  height: 40;\n"
   "  position: absolute;\n"
   "  top: 150px;\n"
   "  left: 150px;\n"
   "  z-index: 10;\n"
   "}\n"
   "</style>\n"
   "</head>\n"
   "<body>\n"
   "<div id=\"wrapper\">\n"
   "<canvas id=\"graph\" width=\"800\" height=\"400\"></canvas>\n"
   "<div id=\"popup\" width=\"60\" height=\"40\"><canvas id=\"tip\" width=\"60\" height=\"40\"></canvas></div>\n"
   "</div>\n"
   "</body>\n"
   "</html>\n";
