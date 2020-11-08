import { Injectable } from '@angular/core';
declare var $
interface Config{
  users:any[],
  fingerSensor:any[],
  light:any[]
  door:any[]
}
interface Status{
    board1:number,
    finger1:number
}
@Injectable({
  providedIn: 'root'
})

export class DataService {
  ws = new WebSocket ('ws://localhost:8080');
  LOAD = false
EVENTS = []
  public CONFIG = {} as Config
  public STATUS = {} as Status
  HOME = {
    init: (data)=>{
      this.STATUS = data.status
      this.CONFIG = data.config
      this.LOAD = true
    },
    setPin:(data)=>{
      let light = this.CONFIG.light.find(a=>{
        console.log(+(data.sensor),a.relayPin)
        return +(data.sensor)==a.relayPin
      })
      if (light){
        console.log(light,data)
        light.status = data.value=="1"?false:true;
      }
      let door = this.CONFIG.door.find(a=>{
        return +(data.sensor)==a.relayPin
      })
      if (door){
        console.log(door,data)
        door.status = data.value=="0"?false:true;
      }


    },
    events:(data)=>{
      this.EVENTS.unshift(`${data.sensor}  ${data.value}`)
    }

  }
  constructor() {
    this.ws.onopen = this.connect
    this.ws.onmessage = this.onmessage.bind(this)
  }
  connect(){
    console.log('CONNECT')
  }
  onmessage(message){
    let data = JSON.parse(message.data)
    console.log("IN",data)
    this.HOME[data.method](data.data)
  }
  send(method,data){
    let d= JSON.stringify({
      method:method,
      data:data
    })
    console.log('[SEND]',d)
    this.ws.send(d)
  }

}
