let convert googlePromise => {
    Js.Promise.make (fun ::resolve reject::_ => {
        resolve googlePromise [@bs];
    });
};