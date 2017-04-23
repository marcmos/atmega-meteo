{-# LANGUAGE OverloadedStrings #-}

module Pollution where

import Data.Aeson.Types
import Network.HTTP.Simple
import Data.Time.Calendar
import Data.Time.Format
import qualified Data.ByteString.Char8 as B

data Measurement = Measurement { timestamp :: String, value :: Double } deriving Show
instance FromJSON Measurement where
  parseJSON json    = do
    [time, pollution] <- parseJSON json
    return $ Measurement time (read pollution)

data Parameter = Parameter { name :: String, measurements :: [Measurement] } deriving Show
instance FromJSON Parameter where
  parseJSON (Object v) = Parameter <$>
    v .: "paramLabel" <*>
    v .: "data"
  parseJSON invalid = typeMismatch "Parameter" invalid

newtype Pollution = Pollution { parameters :: [Parameter] } deriving Show
instance FromJSON Pollution where
  parseJSON (Object v) = Pollution <$> (v .: "data" >>= (.: "series"))
  parseJSON invalid    = typeMismatch "Pollution" invalid

fetchPollution :: Day -> IO (Response Pollution)
fetchPollution date = do
  request <-
    setRequestMethod "POST" .
    setRequestBodyURLEncoded [("query", B.concat ["{\"measType\":\"Auto\",\"viewType\":\"Station\",\"dateRange\":\"Day\",\"date\":\"", B.pack (formatTime defaultTimeLocale "%d.%m.%Y" date), "\",\"viewTypeEntityId\":6,\"channels\":[46,202]}"])] <$>
    parseRequest "http://monitoring.krakow.pios.gov.pl/dane-pomiarowe/pobierz"
  httpJSON request

currentMeasurements :: Pollution -> [(String, Double)]
currentMeasurements pollution = map (\param -> (name param, value . last . measurements $ param)) (parameters pollution)
