let oauth = Youtube.authenticate [%bs.obj {
    authType: "oauth",
    client_id: "clid",
    client_secret: Js.Undefined.return "secret",
    redirect_url: "http://localhost"
}];

Js.log @@ oauth##generateAuthUrl [%bs.obj {
    access_type: "online",
    scope: [| "scope" |]
}];