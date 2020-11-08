import {Component, OnInit} from '@angular/core';
import {DataService} from "./service/data.service";

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit{
  page = 'access';
  createUser = false
  username = 'eeee'
  userId = '2'
  constructor(public ds:DataService) {
  }
  ngOnInit(){

  }
  createNewUser(){
    this.ds.send('createUser',{name:this.username,id:this.userId})
  }
  setLight(id){
    this.ds.send('setLight',{id:id})
  }
  opendoor(id){
    // this.ds.send('setLight',{id:id})
  }
}
