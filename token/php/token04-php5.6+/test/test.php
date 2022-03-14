<?php
require_once '../auto_loader.php';
use ZEGO\ZegoServerAssistant;
use ZEGO\ZegoErrorCodes;

$appId = 1;
$userId = 'demo';
$secret = 'fa94dd0f974cf2e293728a526b028271';
$token = ZegoServerAssistant::generateToken04($appId, $userId, $secret, 3600);
if( $token->code == ZegoErrorCodes::success ){
  #...
}
print_r($token);

//demo
//3AAAAAGCKKT8AEGZvcmtpc2xieW4wdTI4cXcAoPBuvYE1pAu6k+I9aVF4ooQFkG60sNBVZd8quE2Y/lIgkr60HZT5nP1fUgYABO+wpdT7EOJi00k1oycbtpP3E4wsOgAU11gyPSkBVyJ3V4i2nma8v9IPuH5r9WOVSqsngwWDAlBVxjVO14cWyfGc3UDynsALk+qd9Rk8PVrhWTNWpqZxCsUDyk79omSC4wI4CY/wLmiM+AN+wcL9ohGUNbo=
