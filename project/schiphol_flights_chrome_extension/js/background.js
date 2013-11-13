/****************************************************************************
 * background.js
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Runs as a background script in Chrome.
 *
 * Primarily used to receive notification registration,
 * and checking flight data for updates, then displaying
 * the notification if updates have happened.
 ***************************************************************************/

// alarm runs each minute if set
chrome.alarms.onAlarm.addListener(function(alarm)
{
    if (alarm.name == 'flightUpdates')
    {
		// asynchronously get flight_id from storage
    	chrome.storage.local.get('flight_id', function(data)
		{
		    if (!data.flight_id) return; // not set, return

			console.log("Background alarm triggered, flight_id to check is " + data.flight_id);

			// retrieve current data
	        $.get("http://api.schipholapp.nl/chrome_extension/detail.php", {flight_id: data.flight_id, device_language: "EN", chrome: true} )
				.done(function(data)
				{

					flight_data = data.data.flight.actual;
					flight_number = data.data.flight.flight_number;
					status_important = data.data.flight.status_important;
					baggage_handled = data.data.flight.baggage_handled;

					console.log("Flight number is " + flight_number);
					// asynchronously get flight_data from storage
					chrome.storage.local.get('flight_data', function(fdata)
					{
						if (!fdata.flight_data) return; // not set, return

						console.log("Background alarm triggered, flight_data to compare is " + fdata.flight_data);

						// show notification if actual field has changed
						if (flight_data != fdata.flight_data)
						{
							// send notification
							sendNotification(flight_number, flight_data);
							// set up the event listeners
							chrome.notifications.onClosed.addListener(notificationClosed);
							chrome.notifications.onClicked.addListener(notificationClicked);
							chrome.notifications.onButtonClicked.addListener(notificationBtnClick);

							// log event
							console.log("Flight data has changed, notification showed");

							// save data for flight_data
							chrome.storage.local.set({flight_data: flight_data}, function()
							{
							    console.log('Saved (overwritten) flight_data in storage as ' + flight_data);
							});

							// clear alarms when flight no longer changes status
							if (status_important == "Departed" || baggage_handled != '')
							{
								chrome.storage.local.clear();
								chrome.alarms.clearAll();
								console.log("Cleared all alarms and storage data.");
								return;
							}

						}
						else
						{
							console.log("Flight data hasn't changed (yet).");
						}
					});
				}
			);
		});
    }
});

// message receiver
chrome.runtime.onMessage.addListener(function(message,sender,sendResponse)
{
	// save data only if values are not undefined
	if (message.flight_id && message.flight_data && message.flight_number)
	{
		// save data for flight_id
	   	chrome.storage.local.set({flight_id: message.flight_id}, function()
		{
		    console.log('Saved flight_id in storage as ' + message.flight_id);
		});
		// save data for flight_data
		chrome.storage.local.set({flight_data: message.flight_data}, function()
		{
		    console.log('Saved flight_data in storage as ' + message.flight_data);
		});
		// save data for flight_number
		chrome.storage.local.set({flight_number: message.flight_number}, function()
		{
		    console.log('Saved flight_number in storage as ' + message.flight_number);
		});
	}

	// send response
	sendResponse({feedback:"Received message, flight id is set to " + message.flight_id + " , flight_data to " + message.flight_data + " and flight_number to " + message.flight_number});
});

// sends notification
function sendNotification(flight_number, flight_data)
{
	// configure various option settings
	var options =
	{
		type : "basic",
		title: "Flight Update",
		message: "Attention for flight " + flight_number +". " + flight_data + '.',
		iconUrl: "/icons/Schiphol_icon_128_notification.png"
	};

	// jus set to notification id to zero, it doesn't matter here
	var notID = 0;

	// create the notification
	chrome.notifications.create("id"+notID++, options, creationCallback);
}

// notfication callback
function creationCallback(notID)
{
	console.log("Succesfully created " + notID + " notification");
}

// Event handlers for the various notification events
function notificationClosed(notID, bByUser)
{
	console.log("The notification '" + notID + "' was closed" + (bByUser ? " by the user" : ""));
}

function notificationClicked(notID)
{
	console.log("The notification '" + notID + "' was clicked");
}

function notificationBtnClick(notID, iBtn)
{
	console.log("The notification '" + notID + "' had button " + iBtn + " clicked");
}