import { Injectable } from '@angular/core';
declare var $
@Injectable({
  providedIn: 'root'
})
export class DataService {
  ws = new WebSocket ('ws://localhost:8080');
  CONFIG = {}
  HOME = {
    status: (data)=>{
      $('#statuses_board1').css({'background-color': data.statuses.board1==1?'#31E524':'#D74949'})
      $('#statuses_finger1').css({'background-color': data.statuses.finger1==1?'#31E524':'#D74949'})
    },
    config : (data)=>{
      this.CONFIG = data
      console.log(this.CONFIG.config)
      // $('#statuses_board1').css({'background-color': data.statuses.board1==1?'#31E524':'#D74949'})
      // $('#statuses_finger1').css({'background-color': data.statuses.finger1==1?'#31E524':'#D74949'})
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
    console.log(`[IN] ${data.method}`,data.data,this.HOME)
    this.HOME[data.method](data.data)
  }

}
