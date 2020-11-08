const colors = require('colors');
const fs = require('fs');
const Board = new (require('./board'))();
const WebSocket = require('ws');
wss = new WebSocket.Server({ port: 8080 });
CONFIG = JSON.parse(fs.readFileSync('db/db.json', 'utf8'));
// fs.writeFileSync("db/db.json",JSON.stringify(obj));


wss.broadcast = function broadcast(msg) {
    wss.clients.forEach(function each(client) {
        client.send(msg);
    });
};


class Home{
    status = {
        board1:0,
        finger1:0,
        events:[]
    }
    getSensorTemplateLength = function(){
        port.write('getSensorTemplateLength:1\n');
    }
  setLight = function(data){
      let light = CONFIG.light.find(a=>a.id==data.id)
    let val = light.status?1:0
    light.status = val?false:true
    Board.port.write(`setPin:${light.relayPin}:${val}\n`, (err) => {
      if (err) {
        return console.log('Error on write: ', err.message);
      }
    });
  }
  createUser = function(data){

    Board.port.write(`createUser:${data.name}:${data.id}\n`, (err) => {
      if (err) {
        return console.log('Error on write: ', err.message);
      }
    });
  }
}
HOME = new Home()


// Read the port data

// parser.on('data', data =>{
//
//
// // console.log(HOME.status)
// });



wss.on('connection', function connection(ws) {
    wss.broadcast(JSON.stringify({
        method:'init',
        data:{
          status:HOME.status,
          config:CONFIG
        }
    }));

    ws.on('message', function incoming(message) {
        data = JSON.parse(message)
        if (HOME.hasOwnProperty(data.method)){
            HOME[data.method](data.data)
        }

        console.log('received:', data);
    });


});
