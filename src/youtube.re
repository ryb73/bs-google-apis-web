type generateAuthUrlOpts = [%bs.obj: {.
    access_type: string,
    scope: array string
}];

class type t = {
    pub generateAuthUrl : generateAuthUrlOpts => string
} [@bs];

type authOptions = [%bs.obj: {.
    authType: string,
    client_id: string,
    client_secret: Js.undefined string,
    redirect_url: string
}];

external authenticateExt : authOptions => Js.t t = "authenticate" [@@bs.module "youtube-api"];
external typeSet : authOptions => string => unit = "type" [@@bs.set];

let authenticate options => {
    /* `type` is a reserved word in OCaml; this is a workaround */
    typeSet options options##authType;
    authenticateExt options;
};