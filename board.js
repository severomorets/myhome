const SerialPort = require('serialport');
// const port = new SerialPort('COM3', { baudRate: 9600 });
const Readline = require('@serialport/parser-readline');
const fs = require('fs');
module.exports = class Board {

  constructor(port='/dev/ttyUSB0') {
    this.port = new SerialPort(port, { baudRate: 9600 });
    this.port.on("open",()=>{console.log('Board Open')})
    this.parser = this.port.pipe(new Readline({ delimiter: '\n' }));
    this.parser.on('data',this.incoming.bind(this))
  }
  incoming(data){
    data = data.substring(0, data.length - 1)
    let m = data.split(":")
    switch (m[0]){
      case 'status':
        switch (m[1]){
          case 'board1':
            HOME.status.board1 = 1
            break;
          case 'finger':
            HOME.status.finger1 = +m[2]
            break;
          case 'ready':
            setTimeout(this.init.bind(this),2000)
            break;
        }
        console.log(data.blue);
        break;
      case 'setPin':
        wss.broadcast(JSON.stringify({
          method:'setPin',
          data:{
            sensor:m[1],
            value:m[2]
          }
        }));
        break;
        case 'createUser':
          console.log('!!!!!!!!!!!!!!!!!!!',m)
          let user = {
            name:m[1],
            id:+m[2]
          }
          CONFIG.users.push(user)
          wss.broadcast(JSON.stringify({
            method:'createUser',
            data:user
          }));
          fs.writeFileSync("db/db.json",JSON.stringify(CONFIG));
        break;
      case 'finger':
        console.log(m)
        if (m[1]!=='error'){
          let door = CONFIG.door.find(a=>a.id==0)

          // this.port.write(`setPin:${door.relayPin}:${0}\n`, (err) => {
          //   if (err) {
          //     return console.log('Error on write: ', err.message);
          //   }
          // });
          // setTimeout(()=>{
          //   this.port.write(`setPin:${door.relayPin}:${1}\n`, (err) => {
          //     if (err) {
          //       return console.log('Error on write: ', err.message);
          //     }
          //   });
          // },2000)
        }else{
          console.log('ERROR',m)
        }

        // wss.broadcast(JSON.stringify({
        //   method:'finger',
        //   data:{
        //     sensor:m[1],
        //     value:m[2]
        //   }
        // }));
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
  }
  init(){
    function sendInput(item,num){
      setTimeout(()=>{
        if (!item.sensorPin){return}
        this.port.write(`initPin:${item.sensorPin}:INPUT\n` ,(err) => {
          if (err) {
            return console.log('Error on write: ', err.message);
          }
        });
      },num)
    }
    function sendOutput(item,num){
      setTimeout(()=>{
        if (!item.relayPin){return}
        this.port.write(`initPin:${item.relayPin}:OUTPUT\n` ,(err) => {
          if (err) {
            return console.log('Error on write: ', err.message);
          }
        });
      },num)
    }
    function sendDefaultOutput(item,num){
      setTimeout(()=>{
        if (!item.relayPin){return}
        this.port.write(`setPin:${item.relayPin}:0\n` ,(err) => {
          if (err) {
            return console.log('Error on write: ', err.message);
          }
        });
      },num)
    }
    let n = 1000
    // CONFIG.light.map(item=>{
    //
    //   sendOutput.bind(this)(item,n)
    //   n+=500
    //   sendInput.bind(this)(item,n)
    //   n+=500
    //
    //
    // })
    // CONFIG.light.map(item=>{
    //   sendDefaultOutput.bind(this)(item,n)
    //   n+=500
    // })

    CONFIG.light.map(item=>{
      if (item.status){
        sendDefaultOutput.bind(this)(item,n)
      }

      n+=500
    })
  }
}

