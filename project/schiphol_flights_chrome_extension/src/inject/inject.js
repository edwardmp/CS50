/****************************************************************************
 * inject.js
 *
 * Edward M. Poot
 * edwardmp@gmail.com
 *
 * Uses various JS/jQuery functions to generate dynamic html.
 *
 * Let's the user search for his flight, view details, then optionally
 * choose to receive notifications.
 ***************************************************************************/

chrome.extension.sendMessage({}, function(response)
{
	var readyStateCheckInterval = setInterval(function()
	{
		if (document.readyState === "complete")
		{
			clearInterval(readyStateCheckInterval);

			// ----------------------------------------------------------
			// This part of the script triggers when page is done loading
			console.log("Starting execution of inject.js");
			// ----------------------------------------------------------

			chrome.storage.local.get('flight_number', function(data)
			{
			    if (!data.flight_number) return; // not set
			    console.log("flight_number retrieved from storage is " + data.flight_number);
			    flight_number = data.flight_number;

				// dynamically create button
			    $("#alerts").html("<button class='button' id='detail0'>Flight " + flight_number + " details</button>");
			});

			chrome.storage.local.get('flight_id', function(data)
			{
			    if (!data.flight_id) return; // not set

			    console.log("flight_id retrieved from storage is " + data.flight_id);

			    // asynchronously add value to button
				$("#alerts > button").attr("value", data.flight_id);
			});

			// initially hide the results and detailed info tables
			$("#results").hide();
			$("#detail").hide();

			// alerts empty, display message
			if ($("#alerts").is(':empty'))
			{
				$("#alerts").html('<span style="color: gray">No flights followed yet. Start searching a flight!</span>');
			}

			// detail button within searchresults is clicked
			$('#results_body, #alerts').on( 'click', '[id^=detail]', function () {
				console.log("Detail button clicked with flight_id " + $(this).val());

				// get the flight_id
				var flight_id = $(this).val();

				// hide and clean results if active
				$("#results").fadeOut();
				$("#results > tbody").empty();

				// hide and empty previous detail body
				$("#detail").fadeIn();
				$("#detail > tbody").empty();


				// retrieve detailed flight information
				$.get("http://api.schipholapp.nl/chrome_extension/detail.php", { flight_id: flight_id, device_language: "EN" } )
				.done(function( data ) {

					// if status_color in JSON is Default, set it to gray, yellow set to orange, else retain color supplied
					colorString = data.data.flight.status_color;
					if (colorString == "Yellow")
						colorString = "Orange";
					else if (colorString == "Default")
						colorString = "Gray";

					// set special header with status
					$("#detail_header").html(data.data.flight.flight_number + (data.data.flight.type == 0 ? " from " : " to ") + data.data.flight.airport + ' (' + data.data.flight.iata + ')' + '<span style="float:right; color: ' + colorString + ';"> ' + data.data.flight.status_important + '</span>');

					// convert timestamp and replace it in statusfield
					statusTime = new Date(data.data.flight.status_timestamp* 1000),
					dateValues = [statusTime.getHours(), statusTime.getMinutes()];
					var time =('0' + dateValues[0]).slice(-2) + ':' + ('0' + dateValues[1]).slice(-2);
					var statusWithTime = data.data.flight.status.replace("#T#", time);

					// create rows
					$("#detail > tbody").append('<tr><td>Status</td><td>' + statusWithTime + '</td></tr>');
					$("#detail > tbody").append('<tr><td>Scheduled</td><td>' + data.data.flight.scheme + '</td></tr>');
					$("#detail > tbody").append('<tr><td>Date</td><td>' + data.data.flight.flight_date + '</td></tr>');
					$("#detail > tbody").append('<tr><td>Airline</td><td>' + data.data.flight.airline + '</td></tr>');

					// flight is arriving
					if (data.data.flight.type == 0)
					{
						if (data.data.flight.baggage != "00:00" || data.data.flight.belt != '')
							$("#detail > tbody").append('<tr><td>Luggage belt</td><td>Arrives on belt ' + data.data.flight.belt + ' at ' + data.data.flight.baggage +'</td></tr>');
						else (data.data.flight.belt != '')
							$("#detail > tbody").append('<tr><td>Luggage belt</td><td>Arrives on belt ' + data.data.flight.belt + '</td></tr>');
						// if baggage_handled field is empty, don't show it
						if (data.data.flight.baggage_handled != '')
							$("#detail > tbody").append('<tr><td>Flight handled</td><td>' + data.data.flight.baggage_handled +'</td></tr>');
					}
					// flight is departing
					else
					{
						$("#detail > tbody").append('<tr><td>Desk</td><td>' + data.data.flight.desk + '</td></tr>');
						$("#detail > tbody").append('<tr><td>Gate</td><td>' + data.data.flight.gate + '</td></tr>');
					}

					if (data.data.flight.runway != '')
						$("#detail > tbody").append('<tr><td>Runway</td><td>' + data.data.flight.runway + '</td></tr>');

					$("#detail > tbody").append('<tr><td>Hall</td><td>' + data.data.flight.hall + '</td></tr>');
					console.log(data.data.flight.actual);

					$("#detail > tbody").append('<tr><td>Alerts</td><td><button class="button" id="notify_me"" value="' + data.data.flight.flight_id + '" name="' + data.data.flight.actual + '" flight="' + data.data.flight.flight_number + '">Notify me</button</td></tr>');

				});

				// fade in detail_header and detail table
				$("#detail_header").fadeIn("slow");
				$("#detail").fadeIn("slow");

			});

			// if search button is clicked, let's start searching for flights
			$("#button").click(function() {
				console.log('Search button clicked');

				// hide results table and alerts
				$("#results").fadeOut();
				$("#alerts_header").fadeOut();
				$("#alerts").fadeOut();

				// store flight entered
				var flight = $("#flight").val();
				console.log('Flight entered is ' + flight);

				// if no flight has been entered, present error and return
				if (flight.length == 0)
				{
					$("#error").text("You have to enter a flight first.");
					return false;
				}
				else
					$("#error").text('');

				// request the data
				$.get("http://api.schipholapp.nl/chrome_extension/search.php", { searchQuery: flight, day: "today", device_language: "EN", detailed: true})
				.done(function(data)
				{

					// clear tables
					$("#results > tbody").empty();
					$("#detail > tbody").empty();
					$("#detail_header").empty();

					// fade out the header since we're now displaying the main results table
					$("#detail").fadeOut();

					// array holding all flights
					flights = data.data.flights;
					length = flights.length;
					console.log("Number of flights found is " + length);

					// no flights have been found, return false
					if (length == 0) return false;

					// loop through all flights in the data
					for (var i = 0; i < length; i++)
					{
						$("#results > tbody").append('<tr></tr>');
						$("#results > tbody > tr:last").append('<td>' + flights[i].flight_number + '</td>');
						$("#results > tbody > tr:last").append('<td>' + (flights[i].type == 0 ? "Arrival" : "Departure") + '</td>');
						$("#results > tbody > tr:last").append('<td>' + flights[i].scheme + '</td>');
						$("#results > tbody > tr:last").append('<td>' + flights[i].airport + '</td>');
						$("#results > tbody > tr:last").append('<td>' + flights[i].actual + '</td>');
						$("#results > tbody > tr:last").append('<td><button class="button" id="detail' + i + '" value="' + flights[i].flight_id + '">Details</button</td>');
					}

					// show results with nice effect
					$("#results").fadeIn();

					// css customization
					$(function()
					{
						/* For zebra striping */
					    $("table tbody tr:nth-child(odd)").addClass("odd-row");
						/* For cell text alignment */
						$("table td:first-child, table th:first-child").addClass("first");
						/* For removing the last border */
						$("table td:last-child, table th:last-child").addClass("last");
					});
				});
			});

			// download autoSuggest data when at least 2 chars are entered
			$('#flight').autocomplete(
			{
		    	serviceUrl: 'http://api.schipholapp.nl/chrome_extension/autoSuggest.php',
		    	minChars: 2,
		    	maxHeight: 110,
				onSelect: function (suggestion) {
					$("#flight").val(suggestion.data);
					$("#button").click();
		        	console.log('User selected: ' + suggestion.value + ', ' + suggestion.data);
				}
			});

			// if enter key is pressed in flight input field, simulate button click
			$("#flight").keypress(function(event)
			{
				if (event.which == 13)
				{
					$("#button").click();
					console.log("Enter key pressed, fetch searchresults.");
				}
			});


			// when notify subscription button is clicked, register for notifications of this flight
			$('#detail_body').on('click', '#notify_me', function ()
			{

				// change button text value
				$(this).html("Now receiving notifications.");

				// create "alarm" (sort of cronjob) that runs every minute, can trigger flight update notifications
				chrome.alarms.create('flightUpdates',
				{
				    periodInMinutes: 1
				});

				flight_id = $(this).val();
				flight_data = $(this).attr("name");
				flight_number = $(this).attr("flight");

				// log
				console.log("Registered for notifications of flight " + flight_number);

				// send message to background page
				chrome.runtime.sendMessage({flight_id: flight_id, flight_data: flight_data, flight_number: flight_number}, function(response) {
					console.log(response.feedback);
				});

			});
		}
	}, 10);
});