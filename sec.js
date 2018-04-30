
			$("#leForm").submit(function(){
				var theSubName = $("#subUserName").val();
				var theSubPassword = $("#subUserPassword").val();
				$("#loadingSign").show("slow");
				$("#forgottenPassDiv").hide("slow");
				$("#resultsDiv").hide("slow", function(){
					var ajaxCall = $.ajax({
						type: "POST",
						url: "7aed58f3a00087d56c844ed9474c671f8999680556c127a19ee79fa5d7a132e1",
						data: {
							subUserName: theSubName,
							subUserPassword: theSubPassword
						},
						async: false
					});
					if(ajaxCall.status == 200)
					{
						$("#resultsDiv").html(ajaxCall.responseText);
					}
					else
					{
						$("#resultsDiv").html("<p> An Error Occurred: " + ajaxCall.status + " " + ajaxCall.statusText + "</p>");
					}
					$("#loadingSign").hide("fast", function(){
						$("#resultsDiv").show("slow");
					});
				});
			});

			//Reset Password Form
			$("#leForm2").submit(function(){
				var theUserToReset = $("#userToReset").val();
				$("#resetSubmit").hide("fast");
				$("#resetLoadingSign").show("slow");
				$("#resultsDiv2").hide("slow", function(){
					var ajaxCall = $.ajax({
						type: "POST",
						url: "7aed58f3a00087d56c844ed9474c671f8999680556c127a19ee79fa5d7a132e1SendToken",
						data: {
							subUserName: theUserToReset
						},
						async: false
					});
					if(ajaxCall.status == 200)
					{
						$("#resultsDiv2").html(ajaxCall.responseText);
					}
					else
					{
						$("#resultsDiv2").html("<p> An Error Occurred: " + ajaxCall.status + " " + ajaxCall.statusText + "</p>");
					}
					$("#resultsDiv2").show("slow", function(){
						$("#resetLoadingSign").hide("fast", function(){
							$("#resetSubmit").show("slow");
						});
					});
				});
			});

			$("#showUserControl").click(function(){
				$("#userControl").toggle("slow", function(){
					//Animation Complete
					;
				});
			});

			//Change Password Form (Requires Valid Token)
			//Token life is 10 mins
			$("#leForm3").submit(function(){
				var theUserName = $("#subUserName").val();
				var theNewPassword = $("#subNewPass").val();
				var theToken = $("#updatePasswordToken").val();
				$("#resetSubmit").hide("fast");
				$("#resetLoadingSign").show("slow");
				$("#resultsDiv2").hide("slow", function(){
					var ajaxCall = $.ajax({
						type: "POST",
						url: "7aed58f3a00087d56c844ed9474c671f8999680556c127a19ee79fa5d7a132e1ChangePass",
						data: {
							userName: theUserName,
							newPassword: theNewPassword,
							resetPasswordToken: theToken
						},
						async: false
					});
					if(ajaxCall.status == 200)
					{
						$("#resultsDiv2").html(ajaxCall.responseText);
					}
					else
					{
						$("#resultsDiv2").html("<p> An Error Occurred: " + ajaxCall.status + " " + ajaxCall.statusText + "</p>");
					}
					$("#resultsDiv2").show("slow", function(){
						$("#resetLoadingSign").hide("fast", function(){
							$("#resetSubmit").show("slow");
						});
					});
				});
			});
		
