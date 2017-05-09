module Search = {
    type snippet = {.
        channelId: string,
        channelTitle: string,
        title: string,
        description: string
    };

    type idObj = {.
        videoId: string
    };

    type item = {.
        id: Js.t idObj,
        snippet: Js.t snippet
    };

    type result = {.
        result: Js.t {. items: array (Js.t item)}
    };

    let maxResultsLimit = 50;

    type listOptions = {.
        part: string,
        q: string,
        maxResults: Js.undefined int
    };
    external _list : Js.t listOptions => Js.t result = "gapi.client.youtube.search.list" [@@bs.val];

    let list opts => GooglePromise.convert @@ _list opts;
};