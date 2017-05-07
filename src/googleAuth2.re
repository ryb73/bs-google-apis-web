class type isSignedInObj = {
    pub get : unit => bool;
    pub listen : (bool => unit) => unit;
} [@bs];

class type t = {
    pub isSignedIn : Js.t isSignedInObj;
    pub signIn : unit => unit;
} [@bs];

external getAuthInstance : unit => Js.t t = "gapi.auth2.getAuthInstance" [@@bs.val];