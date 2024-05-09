//Creating and connecting STOMP client for communication through websocket
const socket = new SockJS("/silo-websocket")
const stompClient = Stomp.over(socket);

//Subscribing to three topics,
//linking each to method to be executed
//when a message is received
const onConnect = () => {
    stompClient.subscribe("/topic/temperatures/update", onReceivedTempMessage);
    stompClient.subscribe("/topic/humidity/update", onReceivedHumMessage);
    stompClient.subscribe("/topic/distances/update", onReceivedDistMessage);
    stompClient.subscribe("/topic/notification", onReceivedNotifMessage);

    stompClient.send("/app/send/warningSetUp"); //prompting server to send warning notifications
}

const onError = () => {
    console.log("Could not establish WebSocket connection");
}

stompClient.connect({}, onConnect, onError);

const onReceivedTempMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    //Updating card
    const card = document.getElementById("temp-elem");
    card.textContent = payloadBody.tvalue;
}

const onReceivedHumMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    //Updating card
    const card = document.getElementById("humid-elem");
    card.textContent = payloadBody.hvalue;
}

const onReceivedDistMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    //Updating card
    const card = document.getElementById("grain-elem");
    card.textContent = payloadBody.percentage;
}

const onReceivedNotifMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);
    switch (payloadBody.warningType){
        case "temperature":     
            const tempWarningBlock = document.getElementById("tempWarning"); 
            if (payloadBody.warningOn){                  
                tempWarningBlock.classList.add("show");
            } else {
                tempWarningBlock.classList.remove("show");
            }          
            break;
        case "humidity": 
            const humWarningBlock = document.getElementById("humWarning");
            if (payloadBody.warningOn){                  
                humWarningBlock.classList.add("show");
            } else {
                humWarningBlock.classList.remove("show");
            }     
            break;
        case "distance":
            const fullWarningBlock = document.getElementById("fullWarning");
            const popup = document.getElementById("siloFullPopup");
            if (payloadBody.warningOn){
                popup.classList.add("show");
                fullWarningBlock.classList.add("show");
            } else {
                popup.classList.remove("show");
                fullWarningBlock.classList.remove("show");
            }
            break;
    }  
}

const configureClosePopup = () => {
    const closePopupButton = document.getElementById("closePopup");
    const popup = document.getElementById("siloFullPopup");

    closePopupButton.addEventListener(
        "click",
        function () {
            popup.classList.remove("show");
        }
    );
}

document.addEventListener("DOMContentLoaded", function() { 
    configureClosePopup();
});