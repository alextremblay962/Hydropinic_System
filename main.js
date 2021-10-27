const SerialPort = require('serialport')
const port = new SerialPort('COM24', { baudRate: 115200 })


port.on('readable', function () {
    console.log('Data:', port.read().toString())
})

setInterval(() => {
    let date = new Date()

    if(date.getHours() >= 7 && date.getHours() < 21){

        sendDevice("hydro/light1",1)
        sendDevice("hydro/fan", 1)
    }else{
        sendDevice("hydro/light1",0)
        sendDevice("hydro/fan", 0)
    }
    
}, 2000);

function sendDevice(topic, payload) {
    var foo = {
        "topic": topic,
        "payload": payload
    }
    foo = JSON.stringify(foo)
    port.write(foo, function (err) {
        if (err) {
            return console.log('Error on write: ', err.message)
        } 
        //console.log('message written')
    })
}