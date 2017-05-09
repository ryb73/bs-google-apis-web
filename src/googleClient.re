type initOptionsJs = [%bs.obj: {.
    clientId: string,
    scope: string,
    discoveryDocs: array string
}];

external _init : initOptionsJs => Js.Promise.t unit = "gapi.client.init" [@@bs.val];
external _load : string => (unit => unit) => unit = "gapi.load" [@@bs.val];

let getAppFromScope scope => switch scope {
    | `YouTube => `YouTube
    | `YouTubeSSL => `YouTube
    | `YouTubeReadOnly => `YouTube
    | `YouTubePartner => `YouTube
    | `YouTubePartnerChannelAudit => `YouTube
};

let getDiscoveryDocForApp app => switch app {
    | `YouTube => "https://www.googleapis.com/discovery/v1/apis/youtube/v3/rest"
};

let removeDuplicates arr => Js.Array.filteri (fun item index => {
    Js.Array.indexOf item arr == index
}) arr;

let getDiscoveryDocs scopes => scopes
    |> Js.Array.map getAppFromScope
    |> removeDuplicates
    |> Js.Array.map getDiscoveryDocForApp;

let getScopeStringSingle scope => switch scope {
    | `YouTube => "https://www.googleapis.com/auth/youtube"
    | `YouTubeSSL => "https://www.googleapis.com/auth/youtube.force-ssl"
    | `YouTubeReadOnly => "https://www.googleapis.com/auth/youtube.readonly"
    | `YouTubePartner => "https://www.googleapis.com/auth/youtubepartner"
    | `YouTubePartnerChannelAudit => "https://www.googleapis.com/auth/youtubepartner-channel-audit"
};

let getScopeString scopes => scopes
    |> Js.Array.map getScopeStringSingle
    |> Js.Array.joinWith " ";

let init clientId scopes => {
    Js.Promise.make (fun ::resolve reject::_ => {
        _load "client:auth2" (fun _ => {
            let discoveryDocs = getDiscoveryDocs scopes;
            let scopeString = getScopeString scopes;
            let initResult = _init [%bs.obj {
                clientId,
                discoveryDocs: discoveryDocs,
                scope: scopeString
            }];

            resolve initResult [@bs];
        });
    });
};