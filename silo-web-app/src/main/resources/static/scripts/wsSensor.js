/*const socket = new SockJS("/silo-websocket")
const stompClient = Stomp.over(socket);

//Finding page url
const url = window.location.href.split("/");
const urlPath = url[url.length - 1]

//Subscribing to correct topic according to the page
const onConnect = () => {
    switch (urlPath) {
        case "humidities":
            stompClient.subscribe("/topic/humidity/update",  (payload) => onReceivedMessage(payload, "humidity"));
            break;
        case "temperatures":
            stompClient.subscribe("/topic/temperatures/update", (payload) => onReceivedMessage(payload, "temperature"));
            break;
        case "grainheights":
            stompClient.subscribe("/topic/distances/update",  (payload) => onReceivedMessage(payload, "distance"));
            break;
    }
}

const onError = () => {
    console.log("Could not establish WebSocket connection");
}

stompClient.connect({}, onConnect, onError);

//Adding new row with new received data
const insertIntoTable = (tableId, data) => {
    const table = document.getElementById(tableId);

    const tableBody = table.getElementsByTagName("tbody")[0];

    let newRow = tableBody.insertRow(0);

    let idCell = newRow.insertCell();
    idCell.appendChild(document.createTextNode(data.id))

    let temperatureCell = newRow.insertCell();
    temperatureCell.appendChild(document.createTextNode(data.value));

    let datetimeCell = newRow.insertCell();
    datetimeCell.appendChild(document.createTextNode(data.dateTime));
}

const onReceivedMessage = (payload, type) => {
    const payloadBody = JSON.parse(payload.body);

    switch (type) {
        case "temperature":
            insertIntoTable("temperature-table", {id: payloadBody.id, value: payloadBody.tvalue, dateTime: payloadBody.dateTime})
        case "distance":
            insertIntoTable("distance-table", {id: payloadBody.id, value: payloadBody.height, dateTime: payloadBody.dateTime})
            break;
        case "humidity":
            insertIntoTable("humidity-table", {id: payloadBody.id, value: payloadBody.hvalue, dateTime: payloadBody.dateTime})
            handleHumJson(value, dateTime);
            break;
    }
}
*/

