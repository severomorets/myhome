const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
// const port = new SerialPort('/dev/ttyUSB1', { baudRate: 9600 });
const port = new SerialPort('COM3', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));
const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: 8080 });
const fs = require('fs');
var CONFIG = JSON.parse(fs.readFileSync('db/db.json', 'utf8'));
// fs.writeFileSync("db/db.json",JSON.stringify(obj));


wss.broadcast = function broadcast(msg) {
    wss.clients.forEach(function each(client) {
        client.send(msg);
    });
};
const colors = require('colors');
let requests = []
class Home{
    statuses = {
        board1:0,
        finger1:0,
        events:[]
    }
    getSensorTemplateLength = function(){
        port.write('getSensorTemplateLength:1\n', (err) => {
            if (err) {
                return console.log('Error on write: ', err.message);
            }
        });

    }
}

HOME = new Home()

// Read the port data
port.on("open", () => {

    console.log('serial port open');
});
parser.on('data', data =>{
    data = data.substring(0, data.length - 1)
    let m = data.split(":")
    // console.log(m)
    switch (m[0]){
        case 'status':
            switch (m[1]){
                case 'board1':
                    HOME.statuses.board1 = 1
                    break;
                case 'finger':
                    HOME.statuses.finger1 = +m[2]
                    break;
            }
            console.log(data.blue);
            break;
        case 'events':
            wss.broadcast(JSON.stringify({
                method:'events',
                data:{
                    sensor:m[1],
                    value:m[2]
                }
            }));
            break;
        case 'request':
            wss.broadcast(JSON.stringify({
                method:m[0],
                data:{
                    request:m[1],
                    value:m[2]
                }
            }));
            console.log(data.yellow);
            break;
        default:
            console.log(data.red);
            break;
    }

// console.log(HOME.statuses)
});



wss.on('connection', function connection(ws) {
    wss.broadcast(JSON.stringify({
        method:'status',
        data:HOME
    }));
  wss.broadcast(JSON.stringify({
    method:'config',
    data:CONFIG
  }));
    ws.on('message', function incoming(message) {
        data = JSON.parse(message)
        if (HOME.hasOwnProperty(data.method)){
            HOME[data.method]()
        }

        console.log('received:', data);
    });


});
