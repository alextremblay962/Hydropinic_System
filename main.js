const SerialPort = require('serialport')
const Device = require("./device.js")
const port = new SerialPort('COM24', { baudRate: 115200 })

var light1 = new Device("light1", "hydro/light1", port)
var fan = new Device("fan", "hydro/fan", port)



// port.on('readable', function () {
//     console.log('Data:', port.read().toString())
// })

setInterval(() => {
    let date = new Date()

    if(date.getHours() >= 7 && date.getHours() < 21){
        light1.tunrON()
        fan.tunrON()
        // sendDevice("hydro/light1",1)
        // sendDevice("hydro/fan", 1)
    }else{
        // sendDevice("hydro/light1",0)
        // sendDevice("hydro/fan", 0)
    }
}, 2000);




// function sendDevice(topic, payload) {
//     var foo = {
//         "topic": topic,
//         "payload": payload
//     }
//     foo = JSON.stringify(foo) + "\n"
//     port.write(foo, function (err) {
//         if (err) {
//             return console.log('Error on write: ', err.message)
//         } 
//         console.log('message written')
//     })

//     //console.log('Data:', port.read())
// }


// function readData(){
    
// }